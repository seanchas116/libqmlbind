#include "engine.h"
#include "value_p.h"
#include <QQmlEngine>

using namespace qmlbind;

extern "C" {

typedef struct qmlbind_engine_s {
    QQmlEngine *d;
} qmlbind_engine;

qmlbind_engine *qmlbind_engine_new() {
    qmlbind_engine *engine = new qmlbind_engine();
    engine->d = new QQmlEngine();
    return engine;
}

void qmlbind_engine_delete(qmlbind_engine *engine) {
    engine->d->deleteLater();
    delete engine;
}

qmlbind_value *qmlbind_engine_eval(qmlbind_engine *engine, const char *str, const char *file, int lineNumber) {
    QJSValue value = engine->d->evaluate(QString::fromUtf8(str), QString::fromUtf8(file), lineNumber);
    return value_from_QJSValue(value);
}

qmlbind_value *qmlbind_engine_get_global_object(qmlbind_engine *engine) {
    return value_from_QJSValue(engine->d->globalObject());
}

qmlbind_value *qmlbind_engine_new_object(qmlbind_engine *engine) {
    return value_from_QJSValue(engine->d->newObject());
}

qmlbind_value *qmlbind_engine_new_array(qmlbind_engine *engine, unsigned length) {
    return value_from_QJSValue(engine->d->newArray(length));
}

}
