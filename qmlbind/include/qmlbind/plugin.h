#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif


QMLBIND_API qmlbind_plugin *qmlbind_plugin_new(const char *filename);
QMLBIND_API void qmlbind_plugin_release(qmlbind_plugin *self);
QMLBIND_API qmlbind_string *qmlbind_plugin_get_error_string(qmlbind_plugin *self);
QMLBIND_API qmlbind_value *qmlbind_plugin_get_instance(qmlbind_plugin *self, qmlbind_engine *engine);

#ifdef __cplusplus
}
#endif
