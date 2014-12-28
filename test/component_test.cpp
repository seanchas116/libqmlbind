#include "test_helper.h"
#include <qmlbind/component.h>
#include <qmlbind/engine.h>
#include <qmlbind/value.h>
#include <catch.hpp>

TEST_CASE("component")
{
    auto engine = qmlbind_engine_new();

    SECTION("loads a component from data")
    {
        auto data = R"QML(
            import QtQml 2.2
            QtObject {
                property int foo: 124
            }
        )QML";
        auto component = qmlbind_component_new(engine);
        qmlbind_component_set_data(component, data, "");

        auto obj = qmlbind_component_create(component);
        qmlbind_component_delete(component);

        auto foo = qmlbind_value_get_property(obj, "foo");
        REQUIRE(qmlbind_value_get_number(foo) == 124);

        qmlbind_value_delete(foo);
        qmlbind_value_delete(obj);
    }

    qmlbind_engine_delete(engine);
}
