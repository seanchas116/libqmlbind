#include "test_helper.h"
#include <qmlbind.h>
#include <string.h>

TEST_CASE("component")
{
    auto engine = qmlbind_engine_new();
    auto component = qmlbind_component_new(engine);

    SECTION("#create")
    {
        SECTION("with data")
        {
            auto data = R"QML(
                import QtQml 2.2
                QtObject {
                    property int foo: 123
                }
            )QML";
            qmlbind_component_set_data(component, data, "");
        }

        SECTION("with path")
        {
            qmlbind_component_load_path(component, "./fixtures/test.qml");
        }

        auto obj = qmlbind_component_create(component);
        REQUIRE(qmlbind_component_get_error_string(component) == nullptr);

        auto foo = qmlbind_value_get_property(obj, "foo");
        REQUIRE(qmlbind_value_get_number(foo) == 123);

        qmlbind_value_delete(foo);
        qmlbind_value_delete(obj);
    }

    SECTION("#get_error_string")
    {
        auto data = R"QML(
            import WRONGMODULE 1.0
            QtObject {
                property int foo: 123
            }
        )QML";
        qmlbind_component_set_data(component, data, "");
        auto str = qmlbind_component_get_error_string(component);

        REQUIRE(str != nullptr);
        REQUIRE(strlen(qmlbind_string_get(str)) > 0);

        qmlbind_string_delete(str);
    }

    qmlbind_component_delete(component);
    qmlbind_engine_delete(engine);
}
