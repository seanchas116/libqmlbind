#include "qmlbind/value.h"
#include "wrapper.h"
#include <QJSValue>
#include <QJSEngine>

using namespace QmlBind;

extern "C" {

qmlbind_value qmlbind_value_new_undefined()
{
    return new QJSValue(QJSValue::UndefinedValue);
}

qmlbind_value qmlbind_value_new_null()
{
    return new QJSValue(QJSValue::NullValue);
}

void qmlbind_value_release(qmlbind_value self)
{
    delete self;
}

qmlbind_value qmlbind_value_clone(qmlbind_value self)
{
    return new QJSValue(*self);
}

int qmlbind_value_is_equal(qmlbind_value value1, qmlbind_value value2)
{
    return value1->equals(*value2);
}

int qmlbind_value_is_identical(qmlbind_value value1, qmlbind_value value2)
{
    return value1->strictlyEquals(*value2);
}

int qmlbind_value_is_undefined(qmlbind_value self)
{
    return self->isUndefined();
}

int qmlbind_value_is_null(qmlbind_value self)
{
    return self->isNull();
}

int qmlbind_value_is_boolean(qmlbind_value self)
{
    return self->isBool();
}

int qmlbind_value_is_number(qmlbind_value self)
{
    return self->isNumber();
}

int qmlbind_value_is_string(qmlbind_value self)
{
    return self->isString();
}

int qmlbind_value_is_object(qmlbind_value self)
{
    return self->isObject();
}

int qmlbind_value_is_array(qmlbind_value self)
{
    return self->isArray();
}

int qmlbind_value_is_function(qmlbind_value self)
{
    return self->isCallable();
}

int qmlbind_value_is_error(qmlbind_value self)
{
    return self->isError();
}

int qmlbind_value_is_wrapper(qmlbind_value self)
{
    return qmlbind_value_get_handle(self) != 0;
}

qmlbind_value qmlbind_value_new_boolean(int x)
{
    return new QJSValue(bool(x));
}

int qmlbind_value_get_boolean(qmlbind_value self)
{
    return self->toBool();
}

qmlbind_value qmlbind_value_new_number(double x)
{
    return new QJSValue(x);
}

double qmlbind_value_get_number(qmlbind_value self)
{
    return self->toNumber();
}

qmlbind_value qmlbind_value_new_string(int len, const char *str)
{
    return new QJSValue(QString::fromUtf8(str, len));
}

qmlbind_value qmlbind_value_new_string_cstr(const char *str)
{
    return new QJSValue(QString::fromUtf8(str));
}

qmlbind_string qmlbind_value_get_string(qmlbind_value self)
{
    return new QByteArray(self->toString().toUtf8());
}

qmlbind_value qmlbind_value_get_property(qmlbind_value self, const char *key)
{
    return new QJSValue(self->property(QString::fromUtf8(key)));
}

void qmlbind_value_set_property(qmlbind_value self, const char *key, qmlbind_value value)
{
    self->setProperty(QString::fromUtf8(key), *value);
}

int qmlbind_value_delete_property(qmlbind_value value, const char *key)
{
    return value->deleteProperty(key);
}

int qmlbind_value_has_property(qmlbind_value value, const char *key)
{
    return value->hasProperty(key);
}

int qmlbind_value_has_own_property(qmlbind_value value, const char *key)
{
    return value->hasOwnProperty(key);
}

qmlbind_value qmlbind_value_get_prototype(qmlbind_value value)
{
    return new QJSValue(value->prototype());
}

void qmlbind_value_set_prototype(qmlbind_value value, qmlbind_value proto)
{
    value->setPrototype(*proto);
}

qmlbind_value qmlbind_value_get_array_item(qmlbind_value value, int index)
{
    return new QJSValue(value->property(index));
}

void qmlbind_value_set_array_item(qmlbind_value value, int index, qmlbind_value property)
{
    value->setProperty(index, *property);
}

qmlbind_object_handle qmlbind_value_get_handle(qmlbind_value self)
{
    Wrapper *obj = dynamic_cast<Wrapper *>(self->toQObject());
    if (!obj) {
        return 0;
    }
    return obj->handle();
}

static QJSValueList pack_args(int argc, qmlbind_value *argv)
{
    QJSValueList args;
    for (int i = 0; i < argc; ++i) {
        args << *argv[i];
    }
    return args;
}

qmlbind_value qmlbind_value_call(qmlbind_value self, int argc, qmlbind_value *argv)
{
    return new QJSValue(self->call(pack_args(argc, argv)));
}

qmlbind_value qmlbind_value_call_constructor(qmlbind_value function, int argc, qmlbind_value *argv)
{
    return new QJSValue(function->callAsConstructor(pack_args(argc, argv)));
}

qmlbind_value qmlbind_value_call_with_instance(qmlbind_value self, qmlbind_value instance, int argc, qmlbind_value *argv)
{
    return new QJSValue(self->callWithInstance(*instance, pack_args(argc, argv)));
}

}
