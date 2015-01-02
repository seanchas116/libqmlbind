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


