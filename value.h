#ifndef VALUE_H
#define VALUE_H

#include "qmlbind_global.h"

extern "C" {

struct qmlbind_value;

typedef enum {
    QMLBIND_VALUE_UNDEFINED,
    QMLBIND_VALUE_NULL,
    QMLBIND_VALUE_NUMBER,
    QMLBIND_VALUE_STRING,
    QMLBIND_VALUE_ARRAY,
    QMLBIND_VALUE_OBJECT,
    QMLBIND_VALUE_DATE,
    QMLBIND_VALUE_FUNCTION
} qmlbind_value_type;

/* basic */

qmlbind_value *qmlbind_value_new();
void qmlbind_value_delete(qmlbind_value *value);

qmlbind_value_type qmlbind_value_get_type(qmlbind_value *value);

/* collections */

int *qmlbind_value_length(qmlbind_value *value);

/* integer */

qmlbind_value *qmlbind_value_new_number(double x);
double qmlbind_value_get_number(qmlbind_value *value);

/* string */

qmlbind_value *qmlbind_value_new_string(const char *str);
char *qmlbind_value_get_string(qmlbind_value *value);

/* array */

qmlbind_value *qmlbind_value_new_array(size_t count, qmlbind_value **values);
qmlbind_value **qmlbind_value_get_array(qmlbind_value *value);

/* object */

qmlbind_value *qmlbind_value_new_object(size_t count, const char **keys, qmlbind_value **values);
void qmlbind_value_get_object(qmlbind_value *value, qmlbind_value ***where_keys, qmlbind_value ***where_values);

/* date */

qmlbind_value *qmlbind_value_new_date_time(time_t time, time_t utc_offset);
void *qmlbind_value_get_date_time(qmlbind_value *value, time_t time, time_t utc_offset);

/* function */

qmlbind_value *qmlbind_value_call(qmlbind_value *value, size_t argc, qmlbind_value **argv);
qmlbind_value *qmlbind_value_call_with_this(qmlbind_value *value, qmlbind_value *this_value, size_t argc, qmlbind_value **argv);

}

#endif // VALUE_H
