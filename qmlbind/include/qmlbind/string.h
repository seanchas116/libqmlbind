#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API char *qmlbind_string_get(qmlbind_string *str);
QMLBIND_API void qmlbind_string_delete(qmlbind_string *str);

QMLBIND_API int qmlbind_string_list_get_length(qmlbind_string_list *list);
QMLBIND_API char *qmlbind_string_list_get(qmlbind_string_list *list, int index);
QMLBIND_API void qmlbind_string_list_delete(qmlbind_string_list *list);

#ifdef __cplusplus
}
#endif
