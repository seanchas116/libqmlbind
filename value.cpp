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

}
