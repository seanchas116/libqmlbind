#include "interface.h"
#include "engine.h"
#include <QDebug>

namespace QmlBind {

Interface::Interface(qmlbind_client_class* classObject, qmlbind_interface_handlers handlers, SignalEmitter *signalEmitter) :
    mObject(nullptr),
    mHandlers(handlers)
{
    mObject = mHandlers.new_object(classObject, signalEmitter);
}

Interface::Interface(qmlbind_client_object* object, qmlbind_interface_handlers handlers) :
    mObject(object),
    mHandlers(handlers)
{
}

Interface::~Interface()
{
    mHandlers.delete_object(mObject);
}


QJSValue Interface::callMethod(QQmlEngine *engine, const QByteArray &method, int argc, QJSValue **argv) const
{
    QScopedPointer<const QJSValue> result(mHandlers.call_method(qobject_cast<Engine *>(engine), mObject, method, argc, argv));
    return *result;
}

QJSValue Interface::getProperty(QQmlEngine *engine, const QByteArray &property) const
{
    QScopedPointer<const QJSValue> result(mHandlers.get_property(qobject_cast<Engine *>(engine), mObject, property));
    return *result;
}

void Interface::setProperty(QQmlEngine *engine, const QByteArray &property, const QJSValue &value) const
{
    QJSValue val = value;
    mHandlers.set_property(qobject_cast<Engine *>(engine), mObject, property, &val);
}


}
