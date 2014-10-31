#pragma once
#include "qmlbind_global.h"
#include <time.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct qmlbind_value_s qmlbind_value;

/* basic */

QMLBIND_API qmlbind_value *qmlbind_value_new_undefined();
QMLBIND_API qmlbind_value *qmlbind_value_new_null();
QMLBIND_API void qmlbind_value_delete(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_undefined(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_null(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_number(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_string(qmlbind_value *self);
QMLBIND_API int qmlbind_value_is_object(qmlbind_value *self);

/* integer */

QMLBIND_API qmlbind_value *qmlbind_value_new_number(double x);
QMLBIND_API double qmlbind_value_get_number(qmlbind_value *self);

/* string */

QMLBIND_API qmlbind_value *qmlbind_value_new_string(const char *str);
QMLBIND_API char *qmlbind_value_get_string(qmlbind_value *self);

/* array */

QMLBIND_API qmlbind_value *qmlbind_value_new_array(size_t count);

/* object */

QMLBIND_API qmlbind_value *qmlbind_value_new_object(size_t count);

QMLBIND_API qmlbind_value *qmlbind_value_get(qmlbind_value *self, const char *key);
QMLBIND_API void qmlbind_value_set(qmlbind_value *self, const char *key, qmlbind_value *value);

/* date */

QMLBIND_API qmlbind_value *qmlbind_value_new_date_time(time_t time, time_t utc_offset);
QMLBIND_API void *qmlbind_value_get_date_time(qmlbind_value *self, time_t time, time_t utc_offset);

/* function */

QMLBIND_API qmlbind_value *qmlbind_value_call(qmlbind_value *self, size_t argc, qmlbind_value **argv);
QMLBIND_API qmlbind_value *qmlbind_value_call_with_this(qmlbind_value *self, qmlbind_value *target, size_t argc, qmlbind_value **argv);

#ifdef __cplusplus
}
#endif
