#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

QMLBIND_API void qmlbind_signal_emitter_emit(qmlbind_signal_emitter emitter, const char *signal_name, int argc, qmlbind_value *argv);
QMLBIND_API qmlbind_engine qmlbind_signal_emitter_get_engine(qmlbind_signal_emitter emitter);
QMLBIND_API void qmlbind_signal_emitter_release(qmlbind_signal_emitter emitter);

#ifdef __cplusplus
}
#endif
