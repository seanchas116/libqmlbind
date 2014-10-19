#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct qmlbind_object_s qmlbind_object;
typedef struct qmlbind_class_s qmlbind_class;

QMLBIND_API qmlbind_object *qmlbind_object_new(qmlbind_class *klass, void *handle, void (*delete_handle)(void *handle));
QMLBIND_API void qmlbind_object_delete(qmlbind_object *self);

QMLBIND_API void *qmlbind_object_get_handle(qmlbind_object *self);
QMLBIND_API qmlbind_class *qmlbind_object_get_class(qmlbind_object *self);

#ifdef __cplusplus
}
#endif
