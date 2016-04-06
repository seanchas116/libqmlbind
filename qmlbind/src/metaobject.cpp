#include "metaobject.h"
#include "exporter.h"
#include "wrapper.h"
#include <QJSValue>
#include <QMetaMethod>
#include <QDebug>

namespace QmlBind {

MetaObject::MetaObject(std::unique_ptr<const Exporter> &&exporter, std::unique_ptr<QMetaObject, decltype(&free)> prototype) :
    mExporter(std::move(exporter)),
    mPrototype(std::move(prototype))
{
    d = mPrototype->d;
}


Wrapper *MetaObject::newWrapper(qmlbind_client_object *object) const {
    return new Wrapper(shared_from_this(), object, mExporter->callbacks());
}

Wrapper *MetaObject::newObject(void *memory) const {
    return new (memory) Wrapper(shared_from_this(), mExporter->classObject(), mExporter->callbacks());
}

int MetaObject::indexOfSignalName(const char *name) const {
    return mExporter->signalIndexMap().value(name, -1);
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
            *static_cast<QJSValue *>(argv[0]) = wrapper->getProperty(mExporter->propertyMap()[index].name);
        }
        index -= count;
        break;
    }
    case QMetaObject::WriteProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            wrapper->setProperty(mExporter->propertyMap()[index].name, *static_cast<QJSValue *>(argv[0]));
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
                Exporter::Method method = mExporter->methodMap()[index];
                *static_cast<QJSValue *>(argv[0]) = wrapper->callMethod(method.name, method.arity, reinterpret_cast<QJSValue **>(argv + 1));
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

} // namespace QmlBind
