#pragma once
#include "qmlbind_global.h"
#include <time.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif




QMLBIND_API qmlbind_value *qmlbind_value_new_undefined();

QMLBIND_API qmlbind_value *qmlbind_value_new_null();

QMLBIND_API void qmlbind_value_release(qmlbind_value *self);

QMLBIND_API qmlbind_value *qmlbind_value_clone(qmlbind_value *other);

QMLBIND_API int qmlbind_value_is_equal(qmlbind_value *value1, qmlbind_value *value2);

QMLBIND_API int qmlbind_value_is_identical(qmlbind_value *value1, qmlbind_value *value2);

QMLBIND_API int qmlbind_value_is_undefined(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_null(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_boolean(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_number(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_string(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_object(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_array(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_function(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_error(qmlbind_value *self);

QMLBIND_API int qmlbind_value_is_wrapper(qmlbind_value *self);


QMLBIND_API qmlbind_value *qmlbind_value_new_boolean(int value);

QMLBIND_API int qmlbind_value_get_boolean(qmlbind_value *self);


QMLBIND_API qmlbind_value *qmlbind_value_new_number(double value);

QMLBIND_API double qmlbind_value_get_number(qmlbind_value *self);


QMLBIND_API qmlbind_value *qmlbind_value_new_string(int length, const char *value);

QMLBIND_API qmlbind_value *qmlbind_value_new_string_cstr(const char *value);

QMLBIND_API qmlbind_string *qmlbind_value_get_string(qmlbind_value *self);


QMLBIND_API qmlbind_value *qmlbind_value_get_property(qmlbind_value *self, const char *key);

QMLBIND_API void qmlbind_value_set_property(qmlbind_value *self, const char *key, qmlbind_value *value);

QMLBIND_API int qmlbind_value_delete_property(qmlbind_value *self, const char *key);

QMLBIND_API int qmlbind_value_has_property(qmlbind_value *self, const char *key);


QMLBIND_API int qmlbind_value_has_own_property(qmlbind_value *self, const char *key);

QMLBIND_API qmlbind_value *qmlbind_value_get_prototype(qmlbind_value *self);

QMLBIND_API void qmlbind_value_set_prototype(qmlbind_value *self, qmlbind_value *proto);


QMLBIND_API int qmlbind_value_has_index(qmlbind_value *self, int index);

QMLBIND_API qmlbind_value *qmlbind_value_get_array_item(qmlbind_value *self, int index);


QMLBIND_API void qmlbind_value_set_array_item(qmlbind_value *self, int index, qmlbind_value *property);



QMLBIND_API qmlbind_value *qmlbind_value_call(
    qmlbind_value *self,
    int argc,
    qmlbind_value **argv
);

QMLBIND_API qmlbind_value *qmlbind_value_call_constructor(
    qmlbind_value *function,
    int argc,
    qmlbind_value **argv
);

QMLBIND_API qmlbind_value *qmlbind_value_call_with_instance(
    qmlbind_value *self,
    qmlbind_value *instance,
    int argc,
    qmlbind_value **argv
);

QMLBIND_API qmlbind_backref *qmlbind_value_get_backref(qmlbind_value *self);

#ifdef __cplusplus
}
#endif
