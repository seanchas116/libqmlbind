#include "interface.h"
#include "backref.h"
#include "engine.h"
#include <QDebug>

namespace QmlBind {

Interface::Interface(qmlbind_interface_handlers handlers) :
    mHandlers(handlers)
{
    if (!handlers.call_method) {
        qFatal("qmlbind: call_method handler not specified");
    }
    if (!handlers.set_property) {
        qFatal("qmlbind: set_property handler not specified");
    }
    if (!handlers.get_property) {
        qFatal("qmlbind: get_property handler not specified");
    }
    if (!handlers.new_object) {
        qFatal("qmlbind: new_object handler not specified");
    }
    if (!handlers.delete_object) {
        qFatal("qmlbind: delete_object handler not specified");
    }
}

QJSValue Interface::callMethod(QQmlEngine *engine, qmlbind_client_object *object, const QByteArray &method, int argc, QJSValue **argv) const
{
    QScopedPointer<const QJSValue> result(mHandlers.call_method(qobject_cast<Engine *>(engine), object, method, argc, argv));
    return *result;
}

QJSValue Interface::getProperty(QQmlEngine *engine, qmlbind_client_object *object, const QByteArray &property) const
{
    QScopedPointer<const QJSValue> result(mHandlers.get_property(qobject_cast<Engine *>(engine), object, property));
    return *result;
}

void Interface::setProperty(QQmlEngine *engine, qmlbind_client_object *object, const QByteArray &property, const QJSValue &value) const
{
    QJSValue val = value;
    mHandlers.set_property(qobject_cast<Engine *>(engine), object, property, &val);
}

Backref Interface::newObject(qmlbind_client_class *classObject, SignalEmitter *signalEmitter)
{
    return Backref(mHandlers.new_object(classObject, signalEmitter), shared_from_this());
}

void Interface::retainObject(qmlbind_client_object *object)
{
    QMutexLocker locker(&mRefCountMutex);

    if (mRefCount.contains(object)) {
        ++mRefCount[object];
    }
    else {
        mRefCount[object] = 1;
    }
}

void Interface::releaseObject(qmlbind_client_object *object)
{
    QMutexLocker locker(&mRefCountMutex);

    Q_ASSERT(mRefCount.contains(object));
    if (--mRefCount[object] == 0) {
        mHandlers.delete_object(object);
        mRefCount.remove(object);
    }
}

}

