#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QObject>


namespace QmlBind {

class Engine;
class MetaObject;

class Wrapper : public QObject
{
public:
    Wrapper(const std::shared_ptr<const MetaObject> &metaObject, qmlbind_client_class *classObject, qmlbind_client_callbacks callbacks);
    Wrapper(const std::shared_ptr<const MetaObject> &metaObject, qmlbind_client_object *object, qmlbind_client_callbacks callbacks);
    ~Wrapper();

    const QMetaObject *metaObject() const Q_DECL_OVERRIDE;
    int qt_metacall(QMetaObject::Call call, int index, void **argv) Q_DECL_OVERRIDE;

    qmlbind_client_object *clientObject() const { return mClientObject; }
    const std::shared_ptr<const MetaObject> qmlbindMetaObject() const { return mMetaObject; }

    Engine *getEngine() const;

    QJSValue callMethod(const QByteArray &method, int argc, QJSValue **argv) const;
    QJSValue getProperty(const QByteArray &property) const;
    void setProperty(const QByteArray &property, const QJSValue &value) const;


private:

    std::shared_ptr<const MetaObject> mMetaObject;
    qmlbind_client_object *mClientObject;
    qmlbind_client_callbacks mCallbacks;
};

} // namespace QmlBind
