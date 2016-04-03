#include "metaobject.h"
#include "exporter.h"
#include "interface.h"
#include "wrapper.h"
#include <QJSValue>
#include <QMetaMethod>
#include <QDebug>
#include <QQmlEngine>
#include <QQmlContext>

namespace QmlBind {

MetaObject::MetaObject(const QSharedPointer<const Exporter> &exporter) :
    mExporter(exporter),
    mPrototype(exporter->metaObjectBuilder().toMetaObject())
{
    d = mPrototype->d;
}

MetaObject::~MetaObject()
{
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

    QSharedPointer<const Exporter> exporter = mExporter;
    QSharedPointer<Interface> interface = ref.interface();

    switch(call) {
    case QMetaObject::ReadProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            *static_cast<QJSValue *>(argv[0]) = interface->getProperty(engine, ref, exporter->propertyMap()[index].name);
        }
        index -= count;
        break;
    }
    case QMetaObject::WriteProperty:
    {
        int count = propertyCount() - propertyOffset();
        if (index < count) {
            interface->setProperty(engine, ref, exporter->propertyMap()[index].name, *static_cast<QJSValue *>(argv[0]));
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
                Exporter::Method method = exporter->methodMap()[index];
                *static_cast<QJSValue *>(argv[0]) = interface->callMethod(engine, ref, method.name, method.arity, reinterpret_cast<QJSValue **>(argv + 1));
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
