#pragma once

#include "qmlbind/qmlbind_global.h"
#include "classinfo.h"

namespace QmlBind {

class MetaClass
{
public:
    MetaClass(const QByteArray &className, qmlbind_client_class* classObject, qmlbind_client_callbacks callbacks);

    static QByteArray methodSignature(const char *name, int arity);

    void addMethod(const QByteArray &name, int argc);
    void addSignal(const QByteArray &name, const QList<QByteArray> &params);
    void addProperty(const QByteArray &name, const QByteArray &notifySignalName);

    QByteArray className() const { return mClassName; }
    qmlbind_client_class *classObject() const { return mClassObject; }
    qmlbind_client_callbacks callbacks() const { return mCallbacks; }
    QList<MethodInfo> methods() const { return mMethods; }
    QList<PropertyInfo> properties() const { return mProperties; }
    std::shared_ptr<MetaObject> createMetaObject() const;

private:
    void invalidiateMetaObject();

    QByteArray mClassName;
    qmlbind_client_class *mClassObject;
    qmlbind_client_callbacks mCallbacks;
    QList<MethodInfo> mMethods;
    QList<PropertyInfo> mProperties;
    mutable std::shared_ptr<MetaObject> mMetaObject;
};

} // namespace QmlBind
