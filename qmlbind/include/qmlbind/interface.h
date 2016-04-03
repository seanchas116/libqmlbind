#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_interface *qmlbind_interface_new(
    qmlbind_interface_handlers handlers
);

QMLBIND_API void qmlbind_interface_release(qmlbind_interface *interface);

#ifdef __cplusplus
}
#endif
