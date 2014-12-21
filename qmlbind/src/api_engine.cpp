#include "qmlbind/engine.h"
#include "wrapper.h"
#include <QQmlEngine>

using namespace QmlBind;

extern "C" {

qmlbind_engine *qmlbind_engine_new()
{
    return new QQmlEngine();
}

void qmlbind_engine_delete(qmlbind_engine *engine)
{
    engine->deleteLater();
}

qmlbind_value *qmlbind_engine_eval(qmlbind_engine *engine, const char *str, const char *file, int lineNumber)
{
    QJSValue value = engine->evaluate(QString::fromUtf8(str), QString::fromUtf8(file), lineNumber);
    return new QJSValue(value);
}

qmlbind_value *qmlbind_engine_get_global_object(qmlbind_engine *engine)
{
    return new QJSValue(engine->globalObject());
}

qmlbind_value *qmlbind_engine_new_object(qmlbind_engine *engine)
{
    return new QJSValue(engine->newObject());
}

qmlbind_value *qmlbind_engine_new_array(qmlbind_engine *engine, int length)
{
    return new QJSValue(engine->newArray(length));
}

qmlbind_value *qmlbind_engine_new_wrapper(qmlbind_engine *engine, qmlbind_metaobject *metaobj, void *handle, void (*delete_handle)(void *))
{
    Wrapper *obj = new Wrapper(metaobj, handle, delete_handle);

    QQmlEngine::setObjectOwnership(obj, QQmlEngine::JavaScriptOwnership);
    return new QJSValue(engine->newQObject(obj));
}

}
