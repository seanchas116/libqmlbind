#include <catch.hpp>
#include <qmlbind/value.h>

TEST_CASE("value")
{
    qmlbind_value *value;

    SECTION("undefined")
    {
        value = qmlbind_value_new_undefined();
        REQUIRE(qmlbind_value_is_undefined(value));
    }

    SECTION("null")
    {
        value = qmlbind_value_new_null();
        REQUIRE(qmlbind_value_is_null(value));
    }

    SECTION("number")
    {
        value = qmlbind_value_new_number(3.14);
        REQUIRE(qmlbind_value_is_number(value));
        REQUIRE(qmlbind_value_get_number(value) == 3.14);
    }

    SECTION("string")
    {
        auto str = "ほげ";
        value = qmlbind_value_new_string(str);
        auto result = qmlbind_value_get_string(value);

        REQUIRE(qmlbind_value_is_string(value));
        REQUIRE(strcmp(qmlbind_string_get(result), str) == 0);

        qmlbind_string_delete(result);
    }

    qmlbind_value_delete(value);
}
