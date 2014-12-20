#include <catch.hpp>
#include <qmlbind/value.h>
#include <qmlbind/engine.h>

TEST_CASE("engine")
{
    auto engine = qmlbind_engine_new();

    SECTION("eval")
    {
        SECTION("evaluates javascript")
        {
            auto result = qmlbind_engine_eval(engine, "1 + 2 + 3", "", 1);
            REQUIRE(qmlbind_value_get_number(result) == 6);
            qmlbind_value_delete(result);
        }
    }

    SECTION("get_global_object")
    {
        SECTION("returns global object")
        {
            auto global = qmlbind_engine_get_global_object(engine);
            auto arrayClass = qmlbind_value_get(global, "Array");

            REQUIRE(qmlbind_value_is_function(arrayClass));

            qmlbind_value_delete(arrayClass);
            qmlbind_value_delete(global);
        }
    }

    SECTION("new_object")
    {
        SECTION("creates a new object")
        {
            auto object = qmlbind_engine_new_object(engine);

            REQUIRE(qmlbind_value_is_object(object));
            REQUIRE(!qmlbind_value_is_array(object));

            qmlbind_value_delete(object);
        }
    }

    SECTION("new array")
    {
        SECTION("creates a new array")
        {
            auto array = qmlbind_engine_new_array(engine, 10);

            REQUIRE(qmlbind_value_is_array(array));

            auto length = qmlbind_value_get(array, "length");

            REQUIRE(qmlbind_value_get_number(length) == 10);

            qmlbind_value_delete(length);
            qmlbind_value_delete(array);
        }
    }

    qmlbind_engine_delete(engine);
}


