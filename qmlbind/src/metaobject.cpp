#include "metaobject.h"
#include "wrapper.h"
#include <QJSValue>
#include <QMetaMethod>
#include <QDebug>

namespace QmlBind {

MetaObject::MetaObject(const QByteArray &className, const QList<MethodInfo> &methods, const QList<PropertyInfo> &properties,
                       qmlbind_client_class *classObject, qmlbind_client_callbacks callbacks) :
    mMethods(methods),
    mProperties(properties),
    mClassObject(classObject),
    mCallbacks(callbacks)
{
    for (int i = 0; i < mMethods.size(); ++i) {
        auto &&method = mMethods[i];
        if (method.type == MethodType::Signal) {
            mSignalIndexMap[method.name] = i;
        }
    }

    setupData(className);
}

Wrapper *MetaObject::newWrapper(qmlbind_client_object *object) const {
    return new Wrapper(shared_from_this(), object, mCallbacks);
}

Wrapper *MetaObject::newObject(void *memory) const {
    return new (memory) Wrapper(shared_from_this(), mClassObject, mCallbacks);
}

int MetaObject::indexOfSignalName(const char *name) const {
    return mSignalIndexMap.value(name, -1);
}

int MetaObject::metaCall(QObject *object, Call call, int index, void **argv) const
{
    index = object->QObject::qt_metacall(call, index, argv);
    if (index < 0) {
        return index;
    }

    Wrapper *wrapper = static_cast<Wrapper *>(object);

    switch(call) {
    case QMetaObject::ReadProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            *static_cast<QJSValue *>(argv[0]) = wrapper->getProperty(mProperties[index].name);
        }
        index -= count;
        break;
    }
    case QMetaObject::WriteProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            wrapper->setProperty(mProperties[index].name, *static_cast<QJSValue *>(argv[0]));
        }
        index -= count;
        break;
    }
    case QMetaObject::InvokeMetaMethod:
    {
        int count = methodCount() - methodOffset();
        if (index < count) {
            if (method(index + methodOffset()).methodType() == QMetaMethod::Signal) {
                QMetaObject::activate(object, this, index, argv);
            }
            else {
                auto method = mMethods[index];
                *static_cast<QJSValue *>(argv[0]) = wrapper->callMethod(method.name, method.params.size(), reinterpret_cast<QJSValue **>(argv + 1));
            }
        }
        index -= count;
        break;
    }
    case QMetaObject::ResetProperty:
    case QMetaObject::QueryPropertyDesignable:
    case QMetaObject::QueryPropertyScriptable:
    case QMetaObject::QueryPropertyStored:
    case QMetaObject::QueryPropertyEditable:
    case QMetaObject::QueryPropertyUser:
    {
        int count = propertyCount() - propertyOffset();
        index -= count;
        break;
    }
    case QMetaObject::RegisterPropertyMetaType:
    {
        int count = propertyCount() - propertyOffset();

        if (index < count) {
            *static_cast<int *>(argv[0]) = -1;
        }
        index -= count;
        break;
    }
    default:
        break;
    }

    return index;
}

void MetaObject::setupData(const QByteArray &className)
{
    struct ArrayData {
        int ref;
        int size;
        uint alloc : 31;
        uint capacityReserved : 1;
        qptrdiff offset;
    };

    struct StringDataBuilder
    {
        QList<QByteArray> strs;

        uint add(const QByteArray &str) {
            strs << str;
            return strs.size() - 1;
        }

        QVector<uint8_t> build() const {
            int headerSize = strs.size() * sizeof(ArrayData);

            QVector<ArrayData> headers;
            QByteArray strData;

            for (int i = 0; i < strs.size(); ++i) {
                const auto &str = strs[i];
                qptrdiff offset = strData.size() + (strs.size() - i) * sizeof(ArrayData);
                ArrayData header { -1, str.size(), 0, 0, offset };
                headers << header;
                strData.append(str);
                strData.append('\0');
            }

            QVector<uint8_t> data(strData.size() + headerSize);
            memcpy(data.data(), headers.constData(), headerSize);
            memcpy(data.data() + headerSize, strData.constData(), strData.size());
            return data;
        }
    };

    struct MetadataBuilder {
        QVector<uint> metadata;

        struct Placeholder {
            MetadataBuilder *builder;
            int index;
            void setCurrentPos() {
                builder->metadata[index] = builder->metadata.size();
            }
        };

        MetadataBuilder &operator<<(uint value) {
            metadata << value;
            return *this;
        }

        Placeholder makePlaceholder() {
            auto index = metadata.size();
            metadata << 0;
            return Placeholder { this, index };
        }
    };

    StringDataBuilder strData;
    MetadataBuilder metadata;

    // content

    metadata << 7; // revision
    metadata << strData.add(className); // className
    metadata << 0 << 0; // class info
    metadata << mMethods.size(); // methods
    auto methodOffsetPlaceholder = metadata.makePlaceholder();
    metadata << mProperties.size(); // properties
    auto propertyOffsetPlaceholder = metadata.makePlaceholder();
    metadata << 0 << 0; // enums
    metadata << 0 << 0; // constructors
    metadata << 0; // flags

    auto signalCount = std::count_if(mMethods.begin(), mMethods.end(), [](const MethodInfo &method) {
        return method.type == MethodType::Signal;
    });
    metadata << signalCount; // signal count

    methodOffsetPlaceholder.setCurrentPos();

    // methods
    QList<MetadataBuilder::Placeholder> paramPlaceholders;

    for (const auto &method : mMethods) {
        metadata << strData.add(method.name); // name
        metadata << method.params.size(); // argc
        paramPlaceholders << metadata.makePlaceholder(); // offset of parameters
        metadata << 2; // tag
        if (method.type == MethodType::Signal) {
            metadata << 0x06; // flags
        } else {
            metadata << 0x02; // flags
        }
    }
    auto jsValueType = 0x80000000 | strData.add("QJSValue");

    // params
    for (auto i = 0; i < mMethods.size(); ++i) {
        paramPlaceholders[i].setCurrentPos();
        const auto &method = mMethods[i];

        // return type
        if (method.type == MethodType::Signal) {
            metadata << QMetaType::Void;
        } else {
            metadata << jsValueType;
        }

        // parameter types (all QJSValue)
        for (auto i = 0; i < method.params.size(); ++i) {
            metadata << jsValueType;
        }

        // parameter names
        for (auto &&param : method.params) {
            metadata << strData.add(param);
        }
    }

    // properties
    propertyOffsetPlaceholder.setCurrentPos();
    for (const auto &prop : mProperties) {
        metadata << strData.add(prop.name) << jsValueType;
        auto signalIndex = mSignalIndexMap.value(prop.notifySignalName, -1);
        if (signalIndex == -1) {
            qWarning() << "qmlbind: no such notify signal" << prop.notifySignalName << "in class" << className;
            metadata << 0x0009510b;
        } else {
            metadata << 0x0049510b;
        }
    }
    // notify signal ids
    for (const auto &prop : mProperties) {
        auto signalIndex = mSignalIndexMap.value(prop.notifySignalName, 0);
        metadata << signalIndex;
    }

    // end of data
    metadata << 0;

    // put it together

    d.superdata = &QObject::staticMetaObject;
    d.extradata = nullptr;
    d.relatedMetaObjects = nullptr;
    d.static_metacall = nullptr;

    mStringData = strData.build();
    mMetadata = metadata.metadata;
    d.data = mMetadata.data();
    d.stringdata = reinterpret_cast<QArrayData *>(mStringData.data());

}

} // namespace QmlBind
