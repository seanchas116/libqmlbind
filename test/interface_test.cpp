#include "test_helper.h"
#include <catch.hpp>
#include <qmlbind.h>
#include <QMetaObject>
#include <QMetaMethod>
#include <QByteArray>
#include <QDebug>
#include <string.h>

typedef qmlbind_value *(*method_func)(void *, int, qmlbind_value **);
typedef qmlbind_value *(*getter_func)(void *);
typedef void (*setter_func)(void *, qmlbind_value *);

static void *new_obj(void *klass)
{
    // for test purpose returns class (double value) as instance
    *((double *)klass) = 1;
    return klass;
}

static qmlbind_value *invoke_method(void *obj, void *method, int argc, qmlbind_value **argv)
{
    return ((method_func)method)(obj, argc, argv);
}

static qmlbind_value *invoke_getter(void *obj, void *getter)
{
    return ((getter_func)getter)(obj);
}

static void invoke_setter(void *obj, void *setter, qmlbind_value *value)
{
    ((setter_func)setter)(obj, value);
}

static qmlbind_value *double_increment_by(void *self, int argc, qmlbind_value **argv)
{
    REQUIRE(argc == 1);
    *(double *)self += qmlbind_value_get_number(argv[0]);
    return qmlbind_value_new_undefined();
}

static void double_set_value(void *self, qmlbind_value *value)
{
    *(double *)self = qmlbind_value_get_number(value);
}

static qmlbind_value *double_get_value(void *self)
{
    return qmlbind_value_new_number(*(double *)self);
}

static void delete_obj(void *self)
{
    *(double *)self = -1;
}

TEST_CASE("metaobject_exporter")
{
    auto engine = qmlbind_engine_new();

    auto self = 123.0;

    qmlbind_interface_handlers handlers;

    handlers.new_object = new_obj;
    handlers.call_method = invoke_method;
    handlers.set_property = invoke_setter;
    handlers.get_property = invoke_getter;
    handlers.delete_object = delete_obj;

    auto interface = qmlbind_interface_new(&self, "Test", handlers);

    auto notifierIndex = qmlbind_interface_add_signal(interface, "valueChanged", 1);
    auto methodIndex = qmlbind_interface_add_method(interface, (void *)double_increment_by, "incrementBy", 1);

    auto propertyIndex = qmlbind_interface_add_property(interface, (void *)double_get_value, (void *)double_set_value, "value", notifierIndex);

    auto metaobject = qmlbind_metaobject_new(interface);

    SECTION("generated metaobject")
    {
        auto metaobj = reinterpret_cast<QMetaObject *>(metaobject);

        auto methodCount = metaobj->methodCount() - metaobj->methodOffset();
        auto propertyCount = metaobj->propertyCount() - metaobj->propertyOffset();

        REQUIRE(strcmp(metaobj->className(),"Test") == 0);
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
        }

        SECTION("property info")
        {
            auto prop = metaobj->property(propertyIndex + metaobj->propertyOffset());
            REQUIRE(QByteArray(prop.name()) == "value");
        }
    }

    SECTION("created wrapper")
    {
        auto value = qmlbind_engine_new_wrapper(engine, metaobject, &self);

        REQUIRE(qmlbind_value_is_wrapper(value));

        self = 123;

        SECTION("getter")
        {
            auto prop = qmlbind_value_get_property(value, "value");
            REQUIRE(qmlbind_value_get_number(prop) == 123);
            qmlbind_value_delete(prop);
        }

        SECTION("setter")
        {
            auto prop = qmlbind_value_new_number(234);
            qmlbind_value_set_property(value, "value", prop);
            REQUIRE(self == 234);
            qmlbind_value_delete(prop);
        }

        SECTION("method")
        {
            auto offset = qmlbind_value_new_number(100);
            auto func = qmlbind_value_get_property(value, "incrementBy");
            auto result = qmlbind_value_call_with_instance(func, value, 1, &offset);

            REQUIRE(self == 223);

            qmlbind_value_delete(offset);
            qmlbind_value_delete(func);
            qmlbind_value_delete(result);
        }

        qmlbind_value_delete(value);
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
            qDebug() << qmlbind_string_get(error);
            qmlbind_string_delete(error);
        }

        auto obj = qmlbind_component_create(component);

        {
            auto value = qmlbind_value_get_property(obj, "value");

            REQUIRE(qmlbind_value_get_number(value) == 1);

            qmlbind_value_delete(value);
        }

        {
            auto offset = qmlbind_value_new_number(100);
            auto func = qmlbind_value_get_property(obj, "incrementBy");
            auto result = qmlbind_value_call_with_instance(func, obj, 1, &offset);

            REQUIRE(self == 101);

            qmlbind_value_delete(offset);
            qmlbind_value_delete(func);
            qmlbind_value_delete(result);
        }

        qmlbind_value_delete(obj);

        qmlbind_component_delete(component);
    }

    qmlbind_metaobject_delete(metaobject);
    qmlbind_engine_delete(engine);
}
