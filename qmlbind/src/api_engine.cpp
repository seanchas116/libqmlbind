#include "qmlbind/engine.h"
#include "engine.h"
#include "metaobject.h"
#include "wrapper.h"
#include "util.h"
#include <QQmlEngine>
#include <QDebug>
#include <QApplication>

using namespace QmlBind;

extern "C" {

qmlbind_engine *qmlbind_engine_new()
{
    Engine *engine = new Engine();
    QObject::connect(engine, SIGNAL(quit()), QApplication::instance(), SLOT(quit()));
    return engine;
}

void qmlbind_engine_release(qmlbind_engine *self)
{
    self->scheduleDelete();
}

qmlbind_value *qmlbind_engine_eval(qmlbind_engine *self, const char *str, const char *fileName, int lineNumber)
{
    QJSValue value = self->evaluate(QString::fromUtf8(str), QString::fromUtf8(fileName), lineNumber);
    return new QJSValue(value);
}

qmlbind_value *qmlbind_engine_get_global_object(qmlbind_engine *self)
{
    return new QJSValue(self->globalObject());
}

qmlbind_value *qmlbind_engine_new_object(qmlbind_engine *self)
{
    return new QJSValue(self->newObject());
}

qmlbind_value *qmlbind_engine_new_array(qmlbind_engine *self, int length)
{
    return new QJSValue(self->newArray(length));
}

qmlbind_value *qmlbind_engine_new_wrapper(qmlbind_engine *self, qmlbind_metaobject *metaobj, qmlbind_backref *object)
{
    Wrapper *obj = new Wrapper(*metaobj, Backref(object, (*metaobj)->exporter()->classRef().interface()));

    // the generated QJSValue is already has JavaScriptOwnership by default. As it has the only referene to
    // the Wrapper QObject, we need to transfer its ownership to JavaScript, too.
    QQmlEngine::setObjectOwnership(obj, QQmlEngine::JavaScriptOwnership);
    return new QJSValue(self->newQObject(obj));
}

void qmlbind_engine_add_import_path(qmlbind_engine *self, const char *path)
{
    self->addImportPath(path);
}

void qmlbind_engine_collect_garbage(qmlbind_engine *self)
{
    self->collectGarbage();
}

}
