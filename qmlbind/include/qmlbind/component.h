#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

qmlbind_component *qmlbind_component_new(qmlbind_engine *engine);
void qmlbind_component_delete(qmlbind_component *component);

void qmlbind_component_load_path(qmlbind_component *component, const char *path);
void qmlbind_component_set_data(qmlbind_component *component, const char *data, const char *path);

qmlbind_value *qmlbind_component_create(qmlbind_component *component);

#ifdef __cplusplus
}
#endif
