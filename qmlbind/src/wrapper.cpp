#include "wrapper.h"
#include <QJSValue>
#include <QQmlEngine>
#include "metaobject.h"
#include "signalemitter.h"
#include "engine.h"

namespace QmlBind {

Wrapper::Wrapper(const std::shared_ptr<const MetaObject> &metaObject,
                 qmlbind_client_object *clientObject, qmlbind_interface_handlers handlers) :
    mMetaObject(metaObject),
    mClientObject(clientObject),
    mHandlers(handlers)
{
}

Wrapper::Wrapper(const QSharedPointer<const MetaObject> &metaObject,
                 qmlbind_client_class *classObject, qmlbind_interface_handlers handlers) :
    mMetaObject(metaObject),
    mClientObject(nullptr),
    mHandlers(handlers)
{
    SignalEmitter *emitter = new SignalEmitter();
    mClientObject = mHandlers.new_object(classObject, emitter);
    emitter->setWrapper(this);
}

Wrapper::~Wrapper()
{
    mHandlers.delete_object(mClientObject);
}


const QMetaObject *Wrapper::metaObject() const
{
    return mMetaObject.get();
}

int Wrapper::qt_metacall(QMetaObject::Call call, int index, void **argv)
{
    return mMetaObject->metaCall(this, call, index, argv);
}



QJSValue Wrapper::callMethod(QQmlEngine *engine, const QByteArray &method, int argc, QJSValue **argv) const
{
    QScopedPointer<const QJSValue> result(mHandlers.call_method(qobject_cast<Engine *>(engine), mClientObject, method, argc, argv));
    return *result;
}

QJSValue Wrapper::getProperty(QQmlEngine *engine, const QByteArray &property) const
{
    QScopedPointer<const QJSValue> result(mHandlers.get_property(qobject_cast<Engine *>(engine), mClientObject, property));
    return *result;
}

void Wrapper::setProperty(QQmlEngine *engine, const QByteArray &property, const QJSValue &value) const
{
    QJSValue val = value;
    mHandlers.set_property(qobject_cast<Engine *>(engine), mClientObject, property, &val);
}

} // namespace QmlBind
