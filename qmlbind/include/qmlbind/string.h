#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API char *qmlbind_string_get(qmlbind_string str);
QMLBIND_API void qmlbind_string_delete(qmlbind_string str);

#ifdef __cplusplus
}
#endif
