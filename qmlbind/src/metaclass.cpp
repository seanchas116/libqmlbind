#include "metaclass.h"
#include "metaobject.h"
#include <stdexcept>
#include <QVector>
#include <QDebug>

namespace QmlBind {

MetaClass::MetaClass(const QByteArray &className, qmlbind_client_class *classObject, qmlbind_client_callbacks callbacks) :
    mClassName(className),
    mClassObject(classObject),
    mCallbacks(callbacks)
{
    if (!mCallbacks.call_method) {
        qFatal("qmlbind: call_method handler not specified");
    }
    if (!mCallbacks.set_property) {
        qFatal("qmlbind: set_property handler not specified");
    }
    if (!mCallbacks.get_property) {
        qFatal("qmlbind: get_property handler not specified");
    }
    if (!mCallbacks.new_object) {
        qFatal("qmlbind: new_object handler not specified");
    }
    if (!mCallbacks.delete_object) {
        qFatal("qmlbind: delete_object handler not specified");
    }
}

void MetaClass::addMethod(const QByteArray &name, int argc)
{
    QList<QByteArray> params;
    for (int i = 0; i < argc; ++i) {
        params << "";
    }

    Method method;
    method.name = name;
    method.params = params;
    method.type = MethodType::Method;
    mMethods << method;
}

void MetaClass::addSignal(const QByteArray &name, const QList<QByteArray> &params)
{
    Method method;
    method.name = name;
    method.params = params;
    method.type = MethodType::Signal;
    mMethods << method;
}

void MetaClass::addProperty(const QByteArray &name, const QByteArray &notifySignalName)
{
    Property prop;
    prop.name = name;
    prop.notifySignalName = notifySignalName;
    mProperties << prop;
}

std::shared_ptr<MetaObject> MetaClass::createMetaObject() const
{
    if (!mMetaObject) {
        mMetaObject = std::make_shared<MetaObject>(*this);
    }
    return mMetaObject;
}

void MetaClass::invalidiateMetaObject()
{
    mMetaObject = nullptr;
}

} // namespace QmlBind
