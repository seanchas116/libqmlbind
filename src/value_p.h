#pragma once
#include "qmlbind_global.h"

class QJSValue;

namespace qmlbind {

qmlbind_value *value_from_QJSValue(const QJSValue &value);

}
