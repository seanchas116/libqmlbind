#include "test_helper.h"
#include <catch.hpp>
#include <qmlbind/engine.h>
#include <qmlbind/interface.h>
#include <qmlbind/metaobject.h>
#include <qmlbind/value.h>
#include <QMetaObject>
#include <QMetaMethod>
#include <QByteArray>
#include <QDebug>

typedef qmlbind_value *(*method_func)(void *, int, qmlbind_value **);
typedef qmlbind_value *(*getter_func)(void *);
typedef void (*setter_func)(void *, qmlbind_value *);

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

static void double_delete(void *self)
{
    *(double *)self = -1;
}

TEST_CASE("metaobject_exporter")
{
    auto engine = qmlbind_engine_new();

    qmlbind_interface_handlers handlers;
    handlers.call_method = invoke_method;
    handlers.set_property = invoke_setter;
    handlers.get_property = invoke_getter;

    auto interface = qmlbind_interface_new("Test", handlers);

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
        auto self = 123.0;
        auto value = qmlbind_engine_new_wrapper(engine, metaobject, &self, &double_delete);

        REQUIRE(qmlbind_value_is_wrapper(value));

        SECTION("getter")
        {
            auto prop = qmlbind_value_get(value, "value");
            REQUIRE(qmlbind_value_get_number(prop) == 123);
            qmlbind_value_delete(prop);
        }

        SECTION("setter")
        {
            auto prop = qmlbind_value_new_number(234);
            qmlbind_value_set(value, "value", prop);
            REQUIRE(self == 234);
            qmlbind_value_delete(prop);
        }

        SECTION("method")
        {
            auto offset = qmlbind_value_new_number(100);
            auto func = qmlbind_value_get(value, "incrementBy");
            auto result = qmlbind_value_call_with_instance(func, value, 1, &offset);

            REQUIRE(self == 223);

            qmlbind_value_delete(offset);
            qmlbind_value_delete(func);
            qmlbind_value_delete(result);
        }

        qmlbind_value_delete(value);
    }

    qmlbind_metaobject_delete(metaobject);
    qmlbind_engine_delete(engine);
}
