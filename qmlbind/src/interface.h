#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QJSValue>
#include <QSharedPointer>
#include <QMutex>

class QQmlEngine;

namespace QmlBind {

class Backref;

class Interface : public QEnableSharedFromThis<Interface>
{
public:
    Interface(qmlbind_interface_handlers handlers);

    QJSValue callMethod(QQmlEngine *engine, const Backref &obj, const QByteArray &method, int argc, QJSValue **argv) const;
    QJSValue getProperty(QQmlEngine *engine, const Backref &obj, const QByteArray &property) const;
    void setProperty(QQmlEngine *engine, const Backref &obj, const QByteArray &property, const QJSValue &value) const;

    Backref newObject(const Backref &klass, SignalEmitter *signalEmitter);

private:

    friend class Backref;

    void retainObject(qmlbind_backref ref);
    void releaseObject(qmlbind_backref ref);

    qmlbind_interface_handlers mHandlers;
    QHash<qmlbind_backref, int> mRefCount;
    QMutex mRefCountMutex;
};

} // namespace QmlBind
