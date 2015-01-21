#include "test_helper.h"
#include <catch.hpp>
#include <qmlbind.h>
#include <QMetaObject>
#include <QMetaMethod>
#include <QByteArray>
#include <QDebug>
#include <QSharedPointer>
#include <string.h>
#include <functional>

class Test
{
public:

    Test(std::function<void ()> onDestroy) :
        m_value(1),
        m_onDestroy(onDestroy)
    {
    }

    ~Test()
    {
        m_onDestroy();
    }

    void incrementBy(double diff)
    {
        m_value += diff;
    }

    double value()
    {
        return m_value;
    }

    void setValue(double val)
    {
        m_value = val;
    }

    qmlbind_engine engine()
    {
        return m_engine;
    }

    void setEngine(qmlbind_engine engine)
    {
        m_engine = engine;
    }

private:
    double m_value;
    std::function<void ()> m_onDestroy;
    qmlbind_engine m_engine = nullptr;
};

namespace Handlers {

    qmlbind_object_handle newObject(qmlbind_class_handle klass)
    {
        std::string name = (char *)klass;
        REQUIRE(name == "class:Test");
        auto test = new Test([] {});
        return (qmlbind_object_handle)test;
    }

    qmlbind_value invokeMethod(qmlbind_engine engine, qmlbind_object_handle obj, qmlbind_method_handle method, int argc, qmlbind_value *argv)
    {
        std::string name = (char *)method;
        REQUIRE(name == "method:incrementBy");
        REQUIRE(argc == 1);

        auto test = (Test *)obj;
        REQUIRE(test->engine() == engine);
        test->incrementBy(qmlbind_value_get_number(argv[0]));

        return qmlbind_value_new_number(test->value());
    }

    qmlbind_value invokeGetter(qmlbind_engine engine, qmlbind_object_handle obj, qmlbind_getter_handle getter)
    {
        std::string name = (char *)getter;
        REQUIRE(name == "getter:value");

        auto test = (Test *)obj;
        REQUIRE(test->engine() == engine);
        return qmlbind_value_new_number(test->value());
    }

    void invokeSetter(qmlbind_engine engine, qmlbind_object_handle obj, qmlbind_setter_handle setter, qmlbind_value value)
    {
        std::string name = (char *)setter;
        REQUIRE(name == "setter:value");

        auto test = (Test *)obj;
        REQUIRE(test->engine() == engine);
        test->setValue(qmlbind_value_get_number(value));
    }

    void deleteObject(qmlbind_object_handle obj)
    {
        delete (Test *)obj;
    }
}

TEST_CASE("exporter")
{
    auto engine = qmlbind_engine_new();

    qmlbind_interface_handlers handlers;

    handlers.new_object = &Handlers::newObject;
    handlers.call_method = &Handlers::invokeMethod;
    handlers.set_property = &Handlers::invokeSetter;
    handlers.get_property = &Handlers::invokeGetter;
    handlers.delete_object = &Handlers::deleteObject;

    auto exporter = qmlbind_exporter_new((qmlbind_class_handle)"class:Test", "Test", handlers);

    const char *notifierparams[] = { "value" };
    auto notifierIndex = qmlbind_exporter_add_signal(exporter, "valueChanged", 1, notifierparams);
    auto methodIndex = qmlbind_exporter_add_method(exporter, (qmlbind_method_handle)"method:incrementBy", "incrementBy", 1);
    auto propertyIndex = qmlbind_exporter_add_property(exporter, (qmlbind_getter_handle)"getter:value", (qmlbind_setter_handle)"setter:value", "value", notifierIndex);

    auto metaobject = qmlbind_metaobject_new(exporter);
    qmlbind_exporter_release(exporter);

    SECTION("generated metaobject")
    {
        auto metaobj = *reinterpret_cast<QSharedPointer<QMetaObject> *>(metaobject);

        auto methodCount = metaobj->methodCount() - metaobj->methodOffset();
        auto propertyCount = metaobj->propertyCount() - metaobj->propertyOffset();

        REQUIRE(QByteArray(metaobj->className()) == "Test");
        REQUIRE(methodCount == 2);
        REQUIRE(propertyCount == 1);

        SECTION("method info")
        {
            auto method = metaobj->method(methodIndex + metaobj->methodOffset());
            REQUIRE(method.name() == "incrementBy");
            REQUIRE(method.methodType() == QMetaMethod::Method);
        }

        SECTION("notifier signal info")
        {
            auto method = metaobj->method(notifierIndex + metaobj->methodOffset());
            REQUIRE(method.name() == "valueChanged");
            REQUIRE(method.methodType() == QMetaMethod::Signal);
            REQUIRE(method.parameterNames()[0] == "value");
        }

        SECTION("property info")
        {
            auto prop = metaobj->property(propertyIndex + metaobj->propertyOffset());
            REQUIRE(QByteArray(prop.name()) == "value");
        }
    }

    SECTION("created wrapper")
    {
        bool destroyed = false;
        auto test = new Test([&] {
            destroyed = true;
        });

        auto value = qmlbind_engine_new_wrapper(engine, metaobject, (qmlbind_object_handle)test);

        REQUIRE(qmlbind_value_is_wrapper(value));

        test->setValue(123);

        SECTION("getter")
        {
            auto prop = qmlbind_value_get_property(value, "value");
            REQUIRE(qmlbind_value_get_number(prop) == 123);
            qmlbind_value_release(prop);
        }

        SECTION("setter")
        {
            auto prop = qmlbind_value_new_number(234);
            qmlbind_value_set_property(value, "value", prop);
            REQUIRE(test->value() == 234);
            qmlbind_value_release(prop);
        }

        SECTION("method")
        {
            auto offset = qmlbind_value_new_number(100);
            auto func = qmlbind_value_get_property(value, "incrementBy");
            auto result = qmlbind_value_call_with_instance(func, value, 1, &offset);

            REQUIRE(test->value() == 223);

            qmlbind_value_release(offset);
            qmlbind_value_release(func);
            qmlbind_value_release(result);
        }

        qmlbind_value_release(value);

        qmlbind_engine_collect_garbage(engine);

        // process deferred delete events
        qmlbind_process_events();

        REQUIRE(destroyed);
    }

    SECTION("register type")
    {
        auto data = R"QML(
            import QtQml 2.2
            import test 1.0
            Test {
            }
        )QML";

        qmlbind_register_type(metaobject, "test", 1, 0, "Test");

        auto component = qmlbind_component_new(engine);
        qmlbind_component_set_data(component, data, "");

        auto error = qmlbind_component_get_error_string(component);
        if (error) {
            qDebug() << qmlbind_string_get_chars(error);
            qmlbind_string_release(error);
        }

        auto obj = qmlbind_component_create(component);
        auto test = (Test *)qmlbind_value_get_handle(obj);
        test->setEngine(engine);

        {
            auto value = qmlbind_value_get_property(obj, "value");

            REQUIRE(qmlbind_value_get_number(value) == 1);

            qmlbind_value_release(value);
        }

        {
            auto offset = qmlbind_value_new_number(100);
            auto func = qmlbind_value_get_property(obj, "incrementBy");
            auto result = qmlbind_value_call_with_instance(func, obj, 1, &offset);

            REQUIRE(test != nullptr);
            REQUIRE(test->value() == 101);

            qmlbind_value_release(offset);
            qmlbind_value_release(func);
            qmlbind_value_release(result);
        }

        qmlbind_value_release(obj);

        qmlbind_component_release(component);
    }

    qmlbind_metaobject_release(metaobject);
    qmlbind_engine_release(engine);
}
