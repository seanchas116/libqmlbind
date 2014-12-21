#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_interface *qmlbind_interface_new(
    const char *className,
    qmlbind_interface_handlers handlers
);

QMLBIND_API int qmlbind_interface_add_method(
    qmlbind_interface *interface,
    void *handle,
    const char *name,
    int arity
);

QMLBIND_API int qmlbind_interface_add_signal(
    qmlbind_interface *interface,
    const char *name,
    int arity
);

QMLBIND_API int qmlbind_interface_add_property(
    qmlbind_interface *interface,
    void *getterHandle,
    void *setterHandle,
    const char *name,
    int notifierSignalIndex
);

#ifdef __cplusplus
}
#endif
