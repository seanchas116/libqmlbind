#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QJSValue>
#include <QSharedPointer>
#include <QMutex>

class QQmlEngine;
class SignalEmitter;

namespace QmlBind {

class Interface
{
public:
    Interface(qmlbind_client_class *classObject, qmlbind_interface_handlers handlers, SignalEmitter* emitter);
    Interface(qmlbind_client_object *object, qmlbind_interface_handlers handlers);
    ~Interface();

    QJSValue callMethod(QQmlEngine *engine, const QByteArray &method, int argc, QJSValue **argv) const;
    QJSValue getProperty(QQmlEngine *engine, const QByteArray &property) const;
    void setProperty(QQmlEngine *engine, const QByteArray &property, const QJSValue &value) const;

    qmlbind_client_object *clientObject() const { return mObject; }

private:

    qmlbind_client_object *mObject;
    qmlbind_interface_handlers mHandlers;
};

} // namespace QmlBind
