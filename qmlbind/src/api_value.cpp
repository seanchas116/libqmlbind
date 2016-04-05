#include "qmlbind/value.h"
#include "wrapper.h"
#include <QJSValue>
#include <QJSEngine>

using namespace QmlBind;

extern "C" {

qmlbind_value *qmlbind_value_new_undefined()
{
    return new QJSValue(QJSValue::UndefinedValue);
}

qmlbind_value *qmlbind_value_new_null()
{
    return new QJSValue(QJSValue::NullValue);
}

void qmlbind_value_release(qmlbind_value *self)
{
    delete self;
}

qmlbind_value *qmlbind_value_clone(const qmlbind_value *other)
{
    return new QJSValue(*other);
}

int qmlbind_value_is_equal(const qmlbind_value *value1, const qmlbind_value *value2)
{
    return value1->equals(*value2);
}

int qmlbind_value_is_identical(const qmlbind_value *value1, const qmlbind_value *value2)
{
    return value1->strictlyEquals(*value2);
}

int qmlbind_value_is_undefined(const qmlbind_value *self)
{
    return self->isUndefined();
}

int qmlbind_value_is_null(const qmlbind_value *self)
{
    return self->isNull();
}

int qmlbind_value_is_boolean(const qmlbind_value *self)
{
    return self->isBool();
}

int qmlbind_value_is_number(const qmlbind_value *self)
{
    return self->isNumber();
}

int qmlbind_value_is_string(const qmlbind_value *self)
{
    return self->isString();
}

int qmlbind_value_is_object(const qmlbind_value *self)
{
    return self->isObject();
}

int qmlbind_value_is_array(const qmlbind_value *self)
{
    return self->isArray();
}

int qmlbind_value_is_function(const qmlbind_value *self)
{
    return self->isCallable();
}

int qmlbind_value_is_error(const qmlbind_value *self)
{
    return self->isError();
}

int qmlbind_value_is_wrapper(const qmlbind_value *self)
{
    return qmlbind_value_unwrap(self) != nullptr;
}

qmlbind_value *qmlbind_value_new_boolean(int value)
{
    return new QJSValue(static_cast<bool>(value));
}

int qmlbind_value_get_boolean(const qmlbind_value *self)
{
    return self->toBool();
}

qmlbind_value *qmlbind_value_new_number(double value)
{
    return new QJSValue(value);
}

double qmlbind_value_get_number(const qmlbind_value *self)
{
    return self->toNumber();
}

qmlbind_value *qmlbind_value_new_string(int length, const char *value)
{
    return new QJSValue(QString::fromUtf8(value, length));
}

qmlbind_value *qmlbind_value_new_string_cstr(const char *value)
{
    return new QJSValue(QString::fromUtf8(value));
}

qmlbind_string *qmlbind_value_get_string(const qmlbind_value *self)
{
    return new QByteArray(self->toString().toUtf8());
}

qmlbind_value *qmlbind_value_get_property(const qmlbind_value *self, const char *key)
{
    return new QJSValue(self->property(QString::fromUtf8(key)));
}

void qmlbind_value_set_property(qmlbind_value *self, const char *key, const qmlbind_value *value)
{
    QJSValue obj = *self;
    obj.setProperty(QString::fromUtf8(key), *value);
}

int qmlbind_value_delete_property(qmlbind_value *self, const char *key)
{
    QJSValue value = *self;
    return value.deleteProperty(key);
}

int qmlbind_value_has_property(const qmlbind_value *self, const char *key)
{
    return self->hasProperty(key);
}

int qmlbind_value_has_index(const qmlbind_value *self, int index)
{
    return self->hasProperty(QString::number(index));
}

int qmlbind_value_has_own_property(const qmlbind_value *self, const char *key)
{
    return self->hasOwnProperty(key);
}

qmlbind_value *qmlbind_value_get_prototype(const qmlbind_value *self)
{
    return new QJSValue(self->prototype());
}

void qmlbind_value_set_prototype(qmlbind_value *self, const qmlbind_value *proto)
{
    QJSValue obj = *self;
    obj.setPrototype(*proto);
}

qmlbind_value *qmlbind_value_get_array_item(const qmlbind_value *self, int index)
{
    return new QJSValue(self->property(index));
}

void qmlbind_value_set_array_item(qmlbind_value *self, int index, const qmlbind_value *property)
{
    QJSValue obj = *self;
    obj.setProperty(index, *property);
}

qmlbind_client_object *qmlbind_value_unwrap(const qmlbind_value *self)
{
    Wrapper *obj = dynamic_cast<Wrapper *>(self->toQObject());
    if (!obj) {
        return nullptr;
    }
    return obj->interface().clientObject();
}

static QJSValueList pack_args(int argc, const qmlbind_value *const *argv)
{
    QJSValueList args;
    for (int i = 0; i < argc; ++i) {
        args << *argv[i];
    }
    return args;
}

qmlbind_value *qmlbind_value_call(qmlbind_value *self, int argc, const qmlbind_value *const *argv)
{
    QJSValue func = *self;
    return new QJSValue(func.call(pack_args(argc, argv)));
}

qmlbind_value *qmlbind_value_call_constructor(qmlbind_value *self, int argc, const qmlbind_value *const *argv)
{
    QJSValue func = *self;
    return new QJSValue(func.callAsConstructor(pack_args(argc, argv)));
}

qmlbind_value *qmlbind_value_call_with_instance(qmlbind_value *self, qmlbind_value *instance,
                                                int argc, const qmlbind_value *const *argv)
{
    QJSValue func = *self;
    return new QJSValue(func.callWithInstance(*instance, pack_args(argc, argv)));
}

}
