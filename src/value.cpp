#include "value.h"
#include "util_p.h"
#include <QJSValue>

using namespace qmlbind;

extern "C" {

typedef struct qmlbind_value_s {
    QJSValue d;
} qmlbind_value;

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

}
