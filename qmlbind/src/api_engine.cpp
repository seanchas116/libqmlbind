#include "qmlbind/engine.h"
#include "metaobject.h"
#include "wrapper.h"
#include "util.h"
#include "engine.h"
#include "functionwrapper.h"
#include <QDebug>

using namespace QmlBind;

extern "C" {

qmlbind_engine qmlbind_engine_new()
{
    return newSharedPointer(new Engine());
}

void qmlbind_engine_release(qmlbind_engine engine)
{
    delete engine;
}

qmlbind_value qmlbind_engine_eval(qmlbind_engine engine, const char *str, const char *file, int lineNumber)
{
    QJSValue value = (*engine)->evaluate(QString::fromUtf8(str), QString::fromUtf8(file), lineNumber);
    return new QJSValue(value);
}

qmlbind_value qmlbind_engine_get_global_object(qmlbind_engine engine)
{
    return new QJSValue((*engine)->globalObject());
}

qmlbind_value qmlbind_engine_new_object(qmlbind_engine engine)
{
    return new QJSValue((*engine)->newObject());
}

qmlbind_value qmlbind_engine_new_array(qmlbind_engine engine, int length)
{
    return new QJSValue((*engine)->newArray(length));
}

qmlbind_value qmlbind_engine_new_function(
    qmlbind_engine engine,
    qmlbind_value (*callback)(qmlbind_function_data, int, qmlbind_value *),
    qmlbind_function_data data,
    void (*delete_data)(qmlbind_function_data)
)
{
    QJSValue func = (*engine)->newFunction(new FunctionWrapper(callback, data, delete_data));
    return new QJSValue(func);
}

qmlbind_value qmlbind_engine_new_wrapper(qmlbind_engine engine, qmlbind_metaobject metaobj, qmlbind_object_handle handle)
{
    Wrapper *obj = new Wrapper(*metaobj, handle);

    QQmlEngine::setObjectOwnership(obj, QQmlEngine::JavaScriptOwnership);
    return new QJSValue((*engine)->newQObject(obj));
}

void qmlbind_engine_add_import_path(qmlbind_engine engine, const char *path)
{
    (*engine)->addImportPath(path);
}

void qmlbind_engine_collect_garbage(qmlbind_engine engine)
{
    (*engine)->collectGarbage();
}

}
