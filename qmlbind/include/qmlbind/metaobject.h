#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_metaobject qmlbind_metaobject_new(qmlbind_exporter exporter);
QMLBIND_API void qmlbind_metaobject_release(qmlbind_metaobject metaobject);

#ifdef __cplusplus
}
#endif
