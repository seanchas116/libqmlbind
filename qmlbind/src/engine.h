#pragma once

#include <QQmlEngine>
#include "qmlbind/qmlbind_global.h"

namespace QmlBind {

class FunctionWrapper;

class Engine : public QQmlEngine
{
    Q_OBJECT
public:
    Engine();

    QJSValue newFunction(FunctionWrapper *funcWrapper);

private:

    QJSValue mWrapFunction;
};

} // namespace QmlBind
