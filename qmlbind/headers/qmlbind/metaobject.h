#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API
qmlbind_metaobject *qmlbind_metaobject_new(qmlbind_interface *interface);

QMLBIND_API
void qmlbind_metaobject_delete(qmlbind_metaobject *metaobject);

#ifdef __cplusplus
}
#endif
