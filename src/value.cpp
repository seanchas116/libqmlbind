#include "value.h"
#include "util_p.h"
#include <QJSValue>

typedef struct qmlbind_value_s {
    QJSValue d;
} qmlbind_value;

typedef struct qmlbind_string_s {
    QByteArray d;
} qmlbind_string;

namespace qmlbind {

qmlbind_value *value_from_QJSValue(const QJSValue &value) {
    qmlbind_value *self = new qmlbind_value();
    self->d = value;
    return self;
}

}

using namespace qmlbind;

extern "C" {

qmlbind_value *qmlbind_value_new_undefined() {
    qmlbind_value *self = new qmlbind_value();
    return self;
}

qmlbind_value *qmlbind_value_new_null() {
    return value_from_QJSValue(QJSValue::NullValue);
}

void qmlbind_value_delete(qmlbind_value *self) {
    delete self;
}

int qmlbind_value_is_equal(qmlbind_value *value1, qmlbind_value *value2) {
    return value1->d.strictlyEquals(value2->d);
}

int qmlbind_value_is_undefined(qmlbind_value *self) {
    return self->d.isUndefined();
}
int qmlbind_value_is_null(qmlbind_value *self) {
    return self->d.isNull();
}
int qmlbind_value_is_number(qmlbind_value *self) {
    return self->d.isNumber();
}
int qmlbind_value_is_string(qmlbind_value *self) {
    return self->d.isString();
}
int qmlbind_value_is_object(qmlbind_value *self) {
    return self->d.isObject();
}

int qmlbind_value_is_array(qmlbind_value *self) {
    return self->d.isArray();
}

int qmlbind_value_is_function(qmlbind_value *self) {
    return self->d.isCallable();
}

qmlbind_value *qmlbind_value_new_number(double x) {
    return value_from_QJSValue(x);
}

double qmlbind_value_get_number(qmlbind_value *self) {
    return self->d.toNumber();
}

qmlbind_value *qmlbind_value_new_string(const char *str) {
    return value_from_QJSValue(QString::fromUtf8(str));
}

qmlbind_string *qmlbind_value_get_string(qmlbind_value *self) {
    qmlbind_string *str = new qmlbind_string();
    str->d = self->d.toString().toUtf8();
    return str;
}

char *qmlbind_string_get(qmlbind_string *str) {
    return str->d.data();
}

void qmlbind_string_delete(qmlbind_string *str) {
    delete str;
}

qmlbind_value *qmlbind_value_get(qmlbind_value *self, const char *key) {
    return value_from_QJSValue(self->d.property(QString::fromUtf8(key)));
}

void qmlbind_value_set(qmlbind_value *self, const char *key, qmlbind_value *value) {
    self->d.setProperty(QString::fromUtf8(key), value->d);
}



}
