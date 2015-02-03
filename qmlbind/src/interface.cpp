#include "interface.h"
#include "backref.h"
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

QJSValue Interface::callMethod(QQmlEngine *engine, const Backref &obj, const Backref &method, int argc, const QJSValue **argv) const
{
    QScopedPointer<const QJSValue> result(mHandlers.call_method(engine, obj.backref(), method.backref(), argc, argv));
    return *result;
}

QJSValue Interface::getProperty(QQmlEngine *engine, const Backref &obj, const Backref &getter) const
{
    QScopedPointer<const QJSValue> result(mHandlers.get_property(engine, obj.backref(), getter.backref()));
    return *result;
}

void Interface::setProperty(QQmlEngine *engine, const Backref &obj, const Backref &setter, const QJSValue &value) const
{
    mHandlers.set_property(engine, obj.backref(), setter.backref(), &value);
}

Backref Interface::newObject(const Backref &klass)
{
    return Backref(mHandlers.new_object(klass.backref()), sharedFromThis());
}

void Interface::retainObject(qmlbind_backref ref)
{
    if (mRefCount.contains(ref)) {
        ++mRefCount[ref];
    }
    else {
        mRefCount[ref] = 1;
    }
}

void Interface::releaseObject(qmlbind_backref ref)
{
    Q_ASSERT(mRefCount.contains(ref));
    if (--mRefCount[ref] == 0) {
        mHandlers.delete_object(ref);
        mRefCount.remove(ref);
    }
}

}

