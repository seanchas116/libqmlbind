#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QList>

namespace QmlBind {

class Exporter
{
public:

    enum class MethodType {
        Method, Signal
    };

    struct Method {
        MethodType type;
        QByteArray name;
        QList<QByteArray> params;
    };

    struct Property {
        QByteArray name;
        QByteArray notifySignalName;
    };

    Exporter(const QByteArray &className, qmlbind_client_class* classObject, qmlbind_client_callbacks callbacks);

    static QByteArray methodSignature(const char *name, int arity);

    void addMethod(const QByteArray &name, int argc);
    void addSignal(const QByteArray &name, const QList<QByteArray> &params);
    void addProperty(const QByteArray &name, const QByteArray &notifySignalName);

    QByteArray className() const { return mClassName; }
    qmlbind_client_class *classObject() const { return mClassObject; }
    qmlbind_client_callbacks callbacks() const { return mCallbacks; }
    QList<Method> methods() const { return mMethods; }
    QList<Property> properties() const { return mProperties; }

private:

    QByteArray mClassName;
    qmlbind_client_class *mClassObject;
    qmlbind_client_callbacks mCallbacks;
    QList<Method> mMethods;
    QList<Property> mProperties;
};

} // namespace QmlBind
