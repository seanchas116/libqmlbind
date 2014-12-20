#pragma once
#include "qmlbind_global.h"
#include <time.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    QMLBIND_PROPERTY_WRITABLE = 1,
    QMLBIND_PROPERTY_CONFIGURABLE = 1 << 1,
    QMLBIND_PROPERTY_ENUMERABLE = 1 << 2
} qmlbind_property_option;

/* basic */

QMLBIND_API qmlbind_value *qmlbind_value_new_undefined();
QMLBIND_API qmlbind_value *qmlbind_value_new_null();
QMLBIND_API void qmlbind_value_delete(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_equal(qmlbind_value *value1, qmlbind_value *value2);

QMLBIND_API int qmlbind_value_is_undefined(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_null(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_number(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_string(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_object(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_array(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_function(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_wrapper(qmlbind_value *self);

/* number */

QMLBIND_API qmlbind_value *qmlbind_value_new_number(double x);
QMLBIND_API double qmlbind_value_get_number(qmlbind_value *self);

/* string */

QMLBIND_API qmlbind_value *qmlbind_value_new_string(const char *str);
QMLBIND_API qmlbind_string *qmlbind_value_get_string(qmlbind_value *self);

QMLBIND_API char *qmlbind_string_get(qmlbind_string *str);
QMLBIND_API void qmlbind_string_delete(qmlbind_string *str);

/* object (see also: engine.h) */

QMLBIND_API qmlbind_value *qmlbind_value_get(qmlbind_value *self, const char *key);
QMLBIND_API void qmlbind_value_set(qmlbind_value *self, const char *key, qmlbind_value *value);

/* function */

QMLBIND_API qmlbind_value *qmlbind_value_call(qmlbind_value *self, size_t argc, qmlbind_value **argv);
QMLBIND_API qmlbind_value *qmlbind_value_call_with_instance(qmlbind_value *self, qmlbind_value *instance, size_t argc, qmlbind_value **argv);

/* wrapper */

QMLBIND_API void *qmlbind_value_get_handle(qmlbind_value *self);

#ifdef __cplusplus
}
#endif
