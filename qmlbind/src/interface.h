#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QJSValue>
#include <QSharedPointer>
#include <QMutex>

class QQmlEngine;

namespace QmlBind {

class Backref;

class Interface : public std::enable_shared_from_this<Interface>
{
public:
    Interface(qmlbind_interface_handlers handlers);

    QJSValue callMethod(QQmlEngine *engine, const Backref &obj, const QByteArray &method, int argc, QJSValue **argv) const;
    QJSValue getProperty(QQmlEngine *engine, const Backref &obj, const QByteArray &property) const;
    void setProperty(QQmlEngine *engine, const Backref &obj, const QByteArray &property, const QJSValue &value) const;

    Backref newObject(qmlbind_client_class * classObject, SignalEmitter *signalEmitter);

private:

    friend class Backref;

    void retainObject(qmlbind_client_object *object);
    void releaseObject(qmlbind_client_object *object);

    qmlbind_interface_handlers mHandlers;
    QHash<qmlbind_client_object *, int> mRefCount;
    QMutex mRefCountMutex;
};

} // namespace QmlBind
