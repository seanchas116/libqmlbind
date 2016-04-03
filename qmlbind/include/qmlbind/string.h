#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API const char *qmlbind_string_get_chars(qmlbind_string *self);
QMLBIND_API int qmlbind_string_get_length(qmlbind_string *self);
QMLBIND_API void qmlbind_string_release(qmlbind_string *self);

#ifdef __cplusplus
}
#endif
