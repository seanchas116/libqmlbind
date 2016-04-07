#pragma once
#include <QByteArray>
#include <QList>

namespace QmlBind {

enum class MethodType {
    Method, Signal
};

struct MethodInfo {
    MethodType type;
    QByteArray name;
    QList<QByteArray> params;
};

struct PropertyInfo {
    QByteArray name;
    QByteArray notifySignalName;
};

}
