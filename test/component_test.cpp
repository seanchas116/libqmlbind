#include "test_helper.h"
#include <qmlbind.h>

TEST_CASE("component")
{
    auto engine = qmlbind_engine_new();

    SECTION("#create")
    {
        auto component = qmlbind_component_new(engine);

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
        qmlbind_component_delete(component);

        auto foo = qmlbind_value_get_property(obj, "foo");
        REQUIRE(qmlbind_value_get_number(foo) == 123);

        qmlbind_value_delete(foo);
        qmlbind_value_delete(obj);
    }

    qmlbind_engine_delete(engine);
}
