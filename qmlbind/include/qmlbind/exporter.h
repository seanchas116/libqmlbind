#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_exporter qmlbind_exporter_new(
    qmlbind_backref classHandle,
    const char *className,
    qmlbind_interface interface
);

QMLBIND_API void qmlbind_exporter_release(qmlbind_exporter exporter);

QMLBIND_API int qmlbind_exporter_add_method(
    qmlbind_exporter exporter,
    const char *name,
    int arity
);

QMLBIND_API int qmlbind_exporter_add_signal(
    qmlbind_exporter exporter,
    const char *name,
    int arity,
    const char **params
);

QMLBIND_API int qmlbind_exporter_add_property(
    qmlbind_exporter exporter,
    const char *name,
    int notifierSignalIndex
);

#ifdef __cplusplus
}
#endif
