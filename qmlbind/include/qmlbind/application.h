#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_application qmlbind_application_new(int argc, char **argv);
QMLBIND_API void qmlbind_application_release(qmlbind_application app);
QMLBIND_API int qmlbind_application_exec(qmlbind_application app);

QMLBIND_API void qmlbind_process_events();
QMLBIND_API void qmlbind_next_tick(qmlbind_interface interface, void (*func)(qmlbind_backref), qmlbind_backref data);

#ifdef __cplusplus
}
#endif
