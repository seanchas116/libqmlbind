
#include "test_helper.h"
#include <qmlbind.h>

TEST_CASE("plugin")
{
    auto engine = qmlbind_engine_new();

    SECTION("get_instance")
    {
#ifdef Q_OS_MAC
        auto path = "../testplugin/libtestplugin.dylib";
#else
        auto path = "../testplugin/libtestplugin.so";
#endif
        auto plugin = qmlbind_plugin_new(path);

        auto instance = qmlbind_plugin_get_instance(plugin, engine);
        auto test = qmlbind_value_get_property(instance, "test");
        REQUIRE(qmlbind_value_get_number(test) == 12345);
        qmlbind_value_release(test);
        qmlbind_value_release(instance);

        qmlbind_plugin_release(plugin);
    }

    SECTION("get_error")
    {
        auto plugin = qmlbind_plugin_new("./wrong/path");

        auto error = qmlbind_plugin_get_error_string(plugin);
        REQUIRE(qmlbind_string_get_length(error) > 0);
        qmlbind_string_release(error);

        qmlbind_plugin_release(plugin);
    }

    qmlbind_engine_release(engine);
}
