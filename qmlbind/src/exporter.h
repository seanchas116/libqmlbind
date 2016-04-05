#pragma once

#include "qmlbind/qmlbind_global.h"
#include <private/qmetaobjectbuilder_p.h>
#include <QSharedPointer>

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

    Exporter(const char *className, qmlbind_client_class* classObject, QSharedPointer<Interface> interface);

    void addMethod(const char *name, int arity);
    void addSignal(const char *name, const QList<QByteArray> &args);
    void addProperty(const char *name, const char *notifier);

    qmlbind_client_class *classObject() const { return mClassObject; }
    std::shared_ptr<Interface> interface() const { return mClassRef.interface(); }
    QSharedPointer<Interface> interface() const { return mInterface; }

    const QMetaObjectBuilder &metaObjectBuilder() const { return mBuilder; }
    QHash<int, Method> methodMap() const { return mMethodMap; }
    QHash<int, Property> propertyMap() const { return mPropertyMap; }
    QHash<QByteArray, int> signalIndexMap() const { return mSignalIndexMap; }

private:

    qmlbind_client_class *mClassObject;
    std::shared_ptr<Interface> mInterface;
    QHash<int, Method> mMethodMap;
    QHash<int, Property> mPropertyMap;
    QHash<QByteArray, int> mSignalIndexMap;

    QMetaObjectBuilder mBuilder;
};

} // namespace QmlBind
