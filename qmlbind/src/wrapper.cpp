#include "wrapper.h"
#include <QJSValue>
#include <QQmlEngine>
#include <QQmlContext>
#include "metaobject.h"
#include "signalemitter.h"
#include "engine.h"

namespace QmlBind {


Wrapper::Wrapper(const std::shared_ptr<const MetaObject> &metaObject,
                 qmlbind_client_class *classObject, qmlbind_client_callbacks callbacks) :
    mMetaObject(metaObject),
    mClientObject(nullptr),
    mCallbacks(callbacks)
{
    SignalEmitter *emitter = new SignalEmitter(this);
    mClientObject = mCallbacks.new_object(classObject, emitter);
}

Wrapper::Wrapper(const std::shared_ptr<const MetaObject> &metaObject,
                 qmlbind_client_object *object, qmlbind_client_callbacks callbacks) :
    mMetaObject(metaObject),
    mClientObject(object),
    mCallbacks(callbacks)
{
}


Wrapper::~Wrapper()
{
    mCallbacks.delete_object(mClientObject);
}

Engine *Wrapper::getEngine() const {
    QQmlContext *context = QQmlEngine::contextForObject(this);
    return context ? qobject_cast<Engine *>(context->engine()) : nullptr;
}

const QMetaObject *Wrapper::metaObject() const
{
    return mMetaObject.get();
}

int Wrapper::qt_metacall(QMetaObject::Call call, int index, void **argv)
{
    return mMetaObject->metaCall(this, call, index, argv);
}



QJSValue Wrapper::callMethod(const QByteArray &method, int argc, QJSValue **argv) const
{
    QScopedPointer<const QJSValue> result(mCallbacks.call_method(getEngine(), mClientObject, method, argc, argv));
    return *result;
}

QJSValue Wrapper::getProperty(const QByteArray &property) const
{
    QScopedPointer<const QJSValue> result(mCallbacks.get_property(getEngine(), mClientObject, property));
    return *result;
}

void Wrapper::setProperty(const QByteArray &property, const QJSValue &value) const
{
    QJSValue val = value;
    mCallbacks.set_property(getEngine(), mClientObject, property, &val);
}

} // namespace QmlBind
