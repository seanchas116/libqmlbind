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

QJSValue Interface::callMethod(QQmlEngine *engine, const Backref &obj, const QByteArray &method, int argc, QJSValue **argv) const
{
    QScopedPointer<const QJSValue> result(mHandlers.call_method(qobject_cast<Engine *>(engine), obj.backref(), method, argc, argv));
    return *result;
}

QJSValue Interface::getProperty(QQmlEngine *engine, const Backref &obj, const QByteArray &property) const
{
    QScopedPointer<const QJSValue> result(mHandlers.get_property(qobject_cast<Engine *>(engine), obj.backref(), property));
    return *result;
}

void Interface::setProperty(QQmlEngine *engine, const Backref &obj, const QByteArray &property, const QJSValue &value) const
{
    QJSValue val = value;
    mHandlers.set_property(qobject_cast<Engine *>(engine), obj.backref(), property, &val);
}

Backref Interface::newObject(const Backref &klass, SignalEmitter *signalEmitter)
{
    return Backref(mHandlers.new_object(klass.backref(), signalEmitter), sharedFromThis());
}

void Interface::retainObject(qmlbind_backref ref)
{
    QMutexLocker locker(&mRefCountMutex);

    if (mRefCount.contains(ref)) {
        ++mRefCount[ref];
    }
    else {
        mRefCount[ref] = 1;
    }
}

void Interface::releaseObject(qmlbind_backref ref)
{
    QMutexLocker locker(&mRefCountMutex);

    Q_ASSERT(mRefCount.contains(ref));
    if (--mRefCount[ref] == 0) {
        mHandlers.delete_object(ref);
        mRefCount.remove(ref);
    }
}

}

