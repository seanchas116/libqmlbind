#include "engine.h"
#include "functionwrapper.h"

namespace QmlBind {

Engine::Engine() :
    QQmlEngine()
{
    mWrapFunction = evaluate(
        "function (wrapper) {"
        "  return function () {"
        "    return wrapper.call(arguments);"
        "  };"
        "}"
    );
}

QJSValue Engine::newFunction(FunctionWrapper *funcWrapper)
{
    setObjectOwnership(funcWrapper, JavaScriptOwnership);

    QJSValueList args;
    args << newQObject(funcWrapper);
    return mWrapFunction.call(args);
}

} // namespace QmlBind

