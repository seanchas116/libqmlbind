#include <stdio.h>
#include <assert.h>
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


int main(void)
{
    test_value_new_undefined();
    test_value_new_null();
    printf("test passed!\n");
    return 0;
}
