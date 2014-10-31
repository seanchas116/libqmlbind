#include "value.h"
#include "util_p.h"
#include <QJSValue>

using namespace qmlbind;

extern "C" {

typedef struct qmlbind_value_s {
    QJSValue d;
} qmlbind_value;

typedef struct qmlbind_string_s {
    QByteArray d;
} qmlbind_string;

qmlbind_value *qmlbind_value_new_undefined() {
    qmlbind_value *self = new qmlbind_value();
    return self;
}

qmlbind_value *qmlbind_value_new_null() {
    qmlbind_value *self = new qmlbind_value();
    self->d = QJSValue(QJSValue::NullValue);
    return self;
}

void qmlbind_value_delete(qmlbind_value *self) {
    delete self;
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

qmlbind_value *qmlbind_value_new_number(double x) {
    qmlbind_value *self = new qmlbind_value();
    self->d = QJSValue(x);
    return self;
}

double qmlbind_value_get_number(qmlbind_value *self) {
    return self->d.toNumber();
}

qmlbind_value *qmlbind_value_new_string(const char *str) {
    qmlbind_value *self = new qmlbind_value();
    self->d = QJSValue(QString::fromUtf8(str));
    return self;
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

}
