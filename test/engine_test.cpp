#include "test_helper.h"
#include <qmlbind.h>

TEST_CASE("engine")
{
    auto engine = qmlbind_engine_new();

    SECTION("eval")
    {
        SECTION("evaluates javascript")
        {
            auto result = qmlbind_engine_eval(engine, "1 + 2 + 3", "", 1);
            REQUIRE(qmlbind_value_get_number(result) == 6);
            qmlbind_value_release(result);
        }
    }

    SECTION("get_global_object")
    {
        SECTION("returns global object")
        {
            auto global = qmlbind_engine_get_global_object(engine);
            auto arrayClass = qmlbind_value_get_property(global, "Array");

            REQUIRE(qmlbind_value_is_function(arrayClass));

            qmlbind_value_release(arrayClass);
            qmlbind_value_release(global);
        }
    }

    SECTION("new_object")
    {
        SECTION("creates a new object")
        {
            auto object = qmlbind_engine_new_object(engine);

            REQUIRE(qmlbind_value_is_object(object));
            REQUIRE(!qmlbind_value_is_array(object));

            qmlbind_value_release(object);
        }
    }

    SECTION("new array")
    {
        SECTION("creates a new array")
        {
            auto array = qmlbind_engine_new_array(engine, 10);

            REQUIRE(qmlbind_value_is_array(array));

            auto length = qmlbind_value_get_property(array, "length");

            REQUIRE(qmlbind_value_get_number(length) == 10);

            qmlbind_value_release(length);
            qmlbind_value_release(array);
        }
    }

    SECTION("new function")
    {
        auto callback = [] (qmlbind_function_data data, int argc, qmlbind_value *argv) {
            auto base = (int *)data;
            REQUIRE(argc == 2);
            auto result = *base + qmlbind_value_get_number(argv[0]) + qmlbind_value_get_number(argv[1]);
            return qmlbind_value_new_number(result);
        };

        auto deleteData = [] (qmlbind_function_data data) {
            auto base = (int *)data;
            *base = 0;
        };

        int base = 10;

        auto func = qmlbind_engine_new_function(engine, callback, (qmlbind_function_data)&base, deleteData);
        auto arg1 = qmlbind_value_new_number(20);
        auto arg2 = qmlbind_value_new_number(30);
        qmlbind_value args[] = { arg1, arg2 };

        auto result = qmlbind_value_call(func, 2, args);
        REQUIRE(qmlbind_value_get_number(result) == 60);

        qmlbind_value_release(result);
        qmlbind_value_release(arg1);
        qmlbind_value_release(arg2);
        qmlbind_value_release(func);

        qmlbind_engine_collect_garbage(engine);
        qmlbind_process_events();

        REQUIRE(base == 0);
    }

    SECTION("#add_import_path")
    {
        qmlbind_engine_add_import_path(engine, "./fixtures");

        auto data = R"QML(
            import QtQuick 2.0
            import testmodule 1.0
            Test {}
        )QML";

        auto component = qmlbind_component_new(engine);
        qmlbind_component_set_data(component, data, "./fixtures/test.qml");

        auto obj = qmlbind_component_create(component);
        qmlbind_component_release(component);

        auto foo = qmlbind_value_get_property(obj, "foo");
        REQUIRE(qmlbind_value_get_number(foo) == 456);

        qmlbind_value_release(foo);
        qmlbind_value_release(obj);
    }

    qmlbind_engine_release(engine);
}


