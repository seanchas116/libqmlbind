#include "exporter.h"
#include <stdexcept>
#include <QVector>
#include <QDebug>

namespace QmlBind {

Exporter::Exporter(const QByteArray &className, qmlbind_client_class *classObject, qmlbind_client_callbacks callbacks) :
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

void Exporter::addMethod(const QByteArray &name, int argc)
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

void Exporter::addSignal(const QByteArray &name, const QList<QByteArray> &params)
{
    Method method;
    method.name = name;
    method.params = params;
    method.type = MethodType::Signal;
    mMethods << method;
}

void Exporter::addProperty(const QByteArray &name, const QByteArray &notifySignalName)
{
    Property prop;
    prop.name = name;
    prop.notifySignalName = notifySignalName;
    mProperties << prop;
}

} // namespace QmlBind
