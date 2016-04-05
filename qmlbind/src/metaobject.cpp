#include "metaobject.h"
#include "exporter.h"
#include "wrapper.h"
#include <QJSValue>
#include <QMetaMethod>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>

namespace QmlBind {

MetaObject::MetaObject(const std::shared_ptr<const Exporter> &exporter) :
    mExporter(exporter),
    mPrototype(exporter->metaObjectBuilder().toMetaObject(), free)
{
    d = mPrototype->d;
}

MetaObject::~MetaObject()
{
}

Wrapper *MetaObject::newWrapper(qmlbind_client_object *object) const {
    // TODO: does this really work without doing some signal emmiting?
    // I think the only use case for this is setting context properties e.g. on the global object to these values.
    return new Wrapper(shared_from_this(), object, mExporter->interfaceHandlers());
}

Wrapper *MetaObject::newObject(void *memory) const {
    return new (memory) Wrapper(sharedFromThis(), mExporter->classObject(), mExporter->interfaceHandlers());
}

int MetaObject::metaCall(QObject *object, Call call, int index, void **argv) const
{
    index = object->QObject::qt_metacall(call, index, argv);
    if (index < 0) {
        return index;
    }

    Wrapper *wrapper = static_cast<Wrapper *>(object);

    QQmlContext *context = QQmlEngine::contextForObject(object);
    QQmlEngine *engine = context ? context->engine() : 0;

    switch(call) {
    case QMetaObject::ReadProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            *static_cast<QJSValue *>(argv[0]) = wrapper->getProperty(engine, mExporter->propertyMap()[index].name);
        }
        index -= count;
        break;
    }
    case QMetaObject::WriteProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            wrapper->setProperty(engine, mExporter->propertyMap()[index].name, *static_cast<QJSValue *>(argv[0]));
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
                *static_cast<QJSValue *>(argv[0]) = wrapper->callMethod(engine, method.name, method.arity, reinterpret_cast<QJSValue **>(argv + 1));
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
