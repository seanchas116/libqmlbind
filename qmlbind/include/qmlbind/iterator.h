#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_iterator qmlbind_iterator_new(qmlbind_value object);
QMLBIND_API void qmlbind_iterator_release(qmlbind_iterator self);

QMLBIND_API qmlbind_string qmlbind_iterator_get_key(qmlbind_iterator self);
QMLBIND_API qmlbind_value qmlbind_iterator_get_value(qmlbind_iterator self);

QMLBIND_API void qmlbind_iterator_next(qmlbind_iterator self);
QMLBIND_API int qmlbind_iterator_has_next(qmlbind_iterator self);

#ifdef __cplusplus
}
#endif
