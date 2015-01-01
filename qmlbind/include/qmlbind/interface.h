#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_interface qmlbind_interface_new(
    qmlbind_class_handle classHandle,
    const char *className,
    qmlbind_interface_handlers handlers
);

QMLBIND_API int qmlbind_interface_add_method(
    qmlbind_interface interface,
    qmlbind_method_handle handle,
    const char *name,
    int arity
);

QMLBIND_API int qmlbind_interface_add_signal(
    qmlbind_interface interface,
    const char *name,
    int arity
);

QMLBIND_API int qmlbind_interface_add_property(
    qmlbind_interface interface,
    qmlbind_getter_handle getterHandle,
    qmlbind_setter_handle setterHandle,
    const char *name,
    int notifierSignalIndex
);

#ifdef __cplusplus
}
#endif
