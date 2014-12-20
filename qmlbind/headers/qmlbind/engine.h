#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_engine *qmlbind_engine_new();
QMLBIND_API void qmlbind_engine_delete(qmlbind_engine *engine);

QMLBIND_API qmlbind_value *qmlbind_engine_eval(qmlbind_engine *engine, const char *str, const char *file, int lineNumber);
QMLBIND_API qmlbind_value *qmlbind_engine_get_global_object(qmlbind_engine *engine);

QMLBIND_API qmlbind_value *qmlbind_engine_new_object(qmlbind_engine *engine);
QMLBIND_API qmlbind_value *qmlbind_engine_new_array(qmlbind_engine *engine, unsigned length);

QMLBIND_API qmlbind_value *qmlbind_engine_new_wrapper(qmlbind_engine *engine, qmlbind_metaobject *metaobj, void *handle, void (*delete_handle)(void *));

#ifdef __cplusplus
}
#endif
