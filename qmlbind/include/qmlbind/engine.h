#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif


QMLBIND_API qmlbind_engine *qmlbind_engine_new();
QMLBIND_API void qmlbind_engine_release(qmlbind_engine *self);
QMLBIND_API qmlbind_value *qmlbind_engine_eval(
    qmlbind_engine *self,
    const char *str, const char *fileName, int lineNumber
);

QMLBIND_API qmlbind_value *qmlbind_engine_get_global_object(qmlbind_engine *self);
QMLBIND_API qmlbind_value *qmlbind_engine_new_object(qmlbind_engine *self);

QMLBIND_API qmlbind_value *qmlbind_engine_new_array(qmlbind_engine *self, int length);

QMLBIND_API qmlbind_value *qmlbind_engine_new_wrapper(
    qmlbind_engine *self,
    qmlbind_metaobject *metaobj,
    qmlbind_backref *object
);

QMLBIND_API void qmlbind_engine_add_import_path(qmlbind_engine *self, const char *path);

QMLBIND_API void qmlbind_engine_collect_garbage(qmlbind_engine *self);

#ifdef __cplusplus
}
#endif
