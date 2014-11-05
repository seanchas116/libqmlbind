#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "application.h"
#include "value.h"
#include "engine.h"

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

static void test_engine_eval() {
    qmlbind_engine *engine = qmlbind_engine_new();
    qmlbind_value *result = qmlbind_engine_eval(engine, "1 + 2 + 3", "", 1);

    assert(qmlbind_value_get_number(result) == 6);

    qmlbind_engine_delete(engine);
    qmlbind_value_delete(result);
}

static void test_engine_get_global_object() {
    qmlbind_engine *engine;
    qmlbind_value *global;
    qmlbind_value *arrayClass;

    engine = qmlbind_engine_new();
    global = qmlbind_engine_get_global_object(engine);

    arrayClass = qmlbind_value_get(global, "Array");
    assert(qmlbind_value_is_function(arrayClass));

    qmlbind_engine_delete(engine);
    qmlbind_value_delete(global);
    qmlbind_value_delete(arrayClass);
}

static void test_engine_new_object() {
    qmlbind_engine *engine;
    qmlbind_value *object;

    engine = qmlbind_engine_new();
    object = qmlbind_engine_new_object(engine);

    assert(qmlbind_value_is_object(object));
    assert(!qmlbind_value_is_array(object));

    qmlbind_engine_delete(engine);
    qmlbind_value_delete(object);
}

static void test_engine_new_array() {
    qmlbind_engine *engine;
    qmlbind_value *array;
    qmlbind_value *length;

    engine = qmlbind_engine_new();
    array = qmlbind_engine_new_array(engine, 10);

    assert(qmlbind_value_is_array(array));

    length = qmlbind_value_get(array, "length");

    assert(qmlbind_value_get_number(length) == 10);

    qmlbind_engine_delete(engine);
    qmlbind_value_delete(array);
    qmlbind_value_delete(length);
}

int main(int argc, char **argv)
{
    qmlbind_application *app = qmlbind_application_new(argc, argv);

    test_value_new_undefined();
    test_value_new_null();
    test_value_new_number();
    test_value_new_string();

    test_engine_eval();
    test_engine_get_global_object();
    test_engine_new_object();
    test_engine_new_array();

    printf("test passed!\n");

    qmlbind_application_delete(app);

    return 0;
}
