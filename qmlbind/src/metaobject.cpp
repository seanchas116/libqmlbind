#include "metaobject.h"
#include "exporter.h"
#include "interface.h"
#include "wrapper.h"
#include "backref.h"
#include "signalemitter.h"
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
    return new Wrapper(shared_from_this(), Backref(object, mExporter->interface()));
}

Wrapper *MetaObject::newObject(void *memory) const {
    SignalEmitter *emitter = new SignalEmitter();
    qmlbind_client_object *object = mExporter->interface()->newObject(mExporter->classObject(), emitter);

    Wrapper *wrapper = new (memory) Wrapper(sharedFromThis(), Backref(object, mExporter->interface()));
    emitter->setWrapper(wrapper);
    return wrapper;
}

int MetaObject::metaCall(QObject *object, Call call, int index, void **argv) const
{
    index = object->QObject::qt_metacall(call, index, argv);
    if (index < 0) {
        return index;
    }

    Backref ref = static_cast<Wrapper *>(object)->backref();

    QQmlContext *context = QQmlEngine::contextForObject(object);
    QQmlEngine *engine = context ? context->engine() : 0;

    std::shared_ptr<Interface> interface = ref.interface();
    qmlbind_client_object *clientObject = ref.backref();

    switch(call) {
    case QMetaObject::ReadProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            *static_cast<QJSValue *>(argv[0]) = interface->getProperty(engine, clientObject, mExporter->propertyMap()[index].name);
        }
        index -= count;
        break;
    }
    case QMetaObject::WriteProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            interface->setProperty(engine, clientObject, mExporter->propertyMap()[index].name, *static_cast<QJSValue *>(argv[0]));
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
                *static_cast<QJSValue *>(argv[0]) = interface->callMethod(engine, clientObject, method.name, method.arity, reinterpret_cast<QJSValue **>(argv + 1));
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
