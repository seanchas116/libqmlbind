#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API qmlbind_application qmlbind_application_new(int argc, char **argv);
QMLBIND_API void qmlbind_application_release(qmlbind_application app);

QMLBIND_API void qmlbind_process_events();

#ifdef __cplusplus
}
#endif
