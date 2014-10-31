#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "value.h"

static void test_value_new_undefined() {
    qmlbind_value *value = qmlbind_value_new_undefined();
    assert(qmlbind_value_is_undefined(value));
    qmlbind_value_delete(value);
}

static void test_value_new_null() {
    qmlbind_value *value = qmlbind_value_new_null();
    assert(qmlbind_value_is_null(value));
    qmlbind_value_delete(value);
}

static void test_value_new_number() {
    qmlbind_value *value = qmlbind_value_new_number(3.14);

    assert(qmlbind_value_get_number(value) == 3.14);
    assert(qmlbind_value_is_number(value));

    qmlbind_value_delete(value);
}

static void test_value_new_string() {
    const char *str = "ほげ";
    qmlbind_value *value = qmlbind_value_new_string(str);
    qmlbind_string *result = qmlbind_value_get_string(value);

    assert(qmlbind_value_is_string(value));
    assert(strcmp(str, qmlbind_string_get(result)) == 0);

    qmlbind_value_delete(value);
    qmlbind_string_delete(result);
}

int main(void)
{
    test_value_new_undefined();
    test_value_new_null();
    test_value_new_number();
    test_value_new_string();
    printf("test passed!\n");
    return 0;
}
