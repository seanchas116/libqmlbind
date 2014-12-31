#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API int qmlbind_register_type(
    qmlbind_metaobject *metaobjet,
    const char *uri,
    int versionMajor, int versionMinor,
    const char *qmlName
);

#ifdef __cplusplus
}
#endif
