#include "test_helper.h"
#include <catch.hpp>
#include <qmlbind.h>
#include <QList>

TEST_CASE("iterator")
{
    constexpr auto count = 10;

    auto engine = qmlbind_engine_new();
    auto object = qmlbind_engine_new_object(engine);

    for (auto i = 0; i < 10; ++i) {
        auto value = qmlbind_value_new_number(i);
        qmlbind_value_set_property(object, std::to_string(i).data(), value);
        qmlbind_value_release(value);
    }

    auto iterator = qmlbind_iterator_new(object);

    for (auto i = 0; qmlbind_iterator_has_next(iterator); ++i) {
        qmlbind_iterator_next(iterator);

        qmlbind_iterator_get_key(iterator);
        auto key = qmlbind_iterator_get_key(iterator);
        auto value = qmlbind_iterator_get_value(iterator);
        REQUIRE(std::string(qmlbind_string_get_chars(key)) == std::to_string(i));
        REQUIRE(qmlbind_value_get_number(value) == i);

        qmlbind_string_release(key);
        qmlbind_value_release(value);
    }

    qmlbind_iterator_release(iterator);
    qmlbind_value_release(object);
    qmlbind_engine_release(engine);
}
