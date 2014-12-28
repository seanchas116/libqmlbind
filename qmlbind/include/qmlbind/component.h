#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_component *qmlbind_component_new(qmlbind_engine *engine);
QMLBIND_API void qmlbind_component_delete(qmlbind_component *component);

QMLBIND_API void qmlbind_component_load_path(qmlbind_component *component, const char *path);
QMLBIND_API void qmlbind_component_set_data(qmlbind_component *component, const char *data, const char *path);

QMLBIND_API qmlbind_string *qmlbind_component_get_error_string(qmlbind_component *component);

QMLBIND_API qmlbind_value *qmlbind_component_create(qmlbind_component *component);

#ifdef __cplusplus
}
#endif
