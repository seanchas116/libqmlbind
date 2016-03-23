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

    Test(std::function<void ()> onDestroy, qmlbind_signal_emitter emitter) :
        m_value(1),
        m_onDestroy(onDestroy),
        m_emitter(emitter)
    {
    }

    ~Test()
    {
        m_onDestroy();
    }

    void incrementBy(double diff)
    {
        setValue(value() + diff);
    }

    double value()
    {
        return m_value;
    }

    void setValue(double val)
    {
        if (m_value != val) {
            m_value = val;
            if (m_emitter) {
                auto value = qmlbind_value_new_number(val);
                qmlbind_signal_emitter_emit(m_emitter, "valueChanged", 1, &value);
                qmlbind_value_release(value);
            }
        }
    }

    qmlbind_engine engine()
    {
        return m_engine;
    }

    void setEngine(qmlbind_engine engine)
    {
        m_engine = engine;
        REQUIRE(engine == qmlbind_signal_emitter_get_engine(m_emitter));
    }

private:
    double m_value;
    std::function<void ()> m_onDestroy;
    qmlbind_engine m_engine = nullptr;
    qmlbind_signal_emitter m_emitter = nullptr;
};

using TestSP = std::shared_ptr<Test>;
Q_DECLARE_METATYPE(TestSP)

namespace Handlers {

qmlbind_backref variantToBackref(const QVariant variant)
{
    return reinterpret_cast<qmlbind_backref>(new QVariant(variant));
}

QVariant backrefToVariant(qmlbind_backref ref)
{
    return *reinterpret_cast<QVariant *>(ref);
}

qmlbind_backref newObject(qmlbind_backref klass, qmlbind_signal_emitter emitter)
{
    REQUIRE(backrefToVariant(klass).toString() == "class:Test");
    auto variant = QVariant::fromValue(std::make_shared<Test>([] {}, emitter));
    return variantToBackref(variant);
}

qmlbind_value invokeMethod(qmlbind_engine engine, qmlbind_backref obj, const char *method, int argc, qmlbind_value *argv)
{
    auto test = backrefToVariant(obj).value<TestSP>();
    REQUIRE(test);
    REQUIRE(test->engine() == engine);
    REQUIRE(QString(method) == "incrementBy");
    REQUIRE(argc == 1);

    test->incrementBy(qmlbind_value_get_number(argv[0]));
    return qmlbind_value_new_number(test->value());
}

qmlbind_value invokeGetter(qmlbind_engine engine, qmlbind_backref obj, const char *property)
{
    auto test = backrefToVariant(obj).value<TestSP>();
    REQUIRE(test);
    REQUIRE(test->engine() == engine);
    REQUIRE(QString(property) == "value");

    return qmlbind_value_new_number(test->value());
}

void invokeSetter(qmlbind_engine engine, qmlbind_backref obj, const char *property, qmlbind_value value)
{
    auto test = backrefToVariant(obj).value<TestSP>();
    REQUIRE(test);
    REQUIRE(test->engine() == engine);
    REQUIRE(QString(property) == "value");

    test->setValue(qmlbind_value_get_number(value));
}

void deleteObject(qmlbind_backref obj)
{
    delete reinterpret_cast<QVariant *>(obj);
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

    auto exporter = qmlbind_exporter_new(Handlers::variantToBackref("class:Test"), "Test", handlers);

    const char *notifierparams[] = { "value" };
    auto notifierIndex = qmlbind_exporter_add_signal(exporter, "valueChanged", 1, notifierparams);
    auto methodIndex = qmlbind_exporter_add_method(exporter, "incrementBy", 1);
    auto propertyIndex = qmlbind_exporter_add_property(exporter, "value", "valueChanged");

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

        {
            auto test = std::make_shared<Test>([&] {
                destroyed = true;
            }, nullptr);

            auto value = qmlbind_engine_new_wrapper(engine, metaobject, Handlers::variantToBackref(QVariant::fromValue(test)));

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
        }

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
                property bool valueChangedEmitted: false
                onValueChanged: {
                    valueChangedEmitted = true
                }
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
        auto test = Handlers::backrefToVariant(qmlbind_value_get_backref(obj)).value<TestSP>();
        test->setEngine(engine);

        {
            auto value = qmlbind_value_get_property(obj, "value");

            REQUIRE(qmlbind_value_get_number(value) == 1);

            qmlbind_value_release(value);
        }

        {
            auto emitted = qmlbind_value_get_property(obj, "valueChangedEmitted");

            REQUIRE(!qmlbind_value_get_boolean(emitted));

            qmlbind_value_release(emitted);
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

        {
            auto emitted = qmlbind_value_get_property(obj, "valueChangedEmitted");

            REQUIRE(qmlbind_value_get_boolean(emitted));

            qmlbind_value_release(emitted);
        }

        qmlbind_value_release(obj);

        qmlbind_component_release(component);
    }

    qmlbind_metaobject_release(metaobject);
    qmlbind_engine_release(engine);
}
