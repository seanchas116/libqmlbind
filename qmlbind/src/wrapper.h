#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QObject>
#include <QSharedPointer>

class QQmlEngine;

namespace QmlBind {

class MetaObject;

class Wrapper : public QObject
{
public:
    Wrapper(const std::shared_ptr<const MetaObject> &metaObject, qmlbind_client_object *clientObject, qmlbind_interface_handlers handlers);
    Wrapper(const std::shared_ptr<const MetaObject> &metaObject, qmlbind_client_class *classObject, qmlbind_interface_handlers handlers);
    ~Wrapper();

    const QMetaObject *metaObject() const Q_DECL_OVERRIDE;
    int qt_metacall(QMetaObject::Call call, int index, void **argv) Q_DECL_OVERRIDE;

    qmlbind_client_object *clientObject() const { return mClientObject; }
    const std::shared_ptr<const MetaObject> qmlbindMetaObject() const { return mMetaObject; }

    QJSValue callMethod(QQmlEngine *engine, const QByteArray &method, int argc, QJSValue **argv) const;
    QJSValue getProperty(QQmlEngine *engine, const QByteArray &property) const;
    void setProperty(QQmlEngine *engine, const QByteArray &property, const QJSValue &value) const;


private:

    std::shared_ptr<const MetaObject> mMetaObject;
    qmlbind_client_object *mClientObject;
    qmlbind_interface_handlers mHandlers;
};

} // namespace QmlBind
