#pragma once

#include "qmlbind/qmlbind_global.h"
#include <private/qmetaobjectbuilder_p.h>

namespace QmlBind {

class Exporter
{
public:

    struct Method {
        QByteArray name;
        int arity;
    };

    struct Property {
        QByteArray name;
    };

    Exporter(const char *className, qmlbind_client_class* classObject, qmlbind_client_callbacks callbacks);

    static QByteArray methodSignature(const char *name, int arity);

    void addMethod(const char *name, int arity);
    void addSignal(const char *name, const QList<QByteArray> &args);
    void addProperty(const char *name, const char *notifier);

    qmlbind_client_class *classObject() const { return mClassObject; }
    qmlbind_client_callbacks callbacks() const { return mCallbacks; }

    std::unique_ptr<QMetaObject, decltype(&free)> toMetaObject() const;
    QHash<int, Method> methodMap() const { return mMethodMap; }
    QHash<int, Property> propertyMap() const { return mPropertyMap; }
    QHash<QByteArray, int> signalIndexMap() const { return mSignalIndexMap; }

private:

    qmlbind_client_class *mClassObject;
    qmlbind_client_callbacks mCallbacks;
    QHash<int, Method> mMethodMap;
    QHash<int, Property> mPropertyMap;
    QHash<QByteArray, int> mSignalIndexMap;

    QMetaObjectBuilder mBuilder;
};

} // namespace QmlBind
