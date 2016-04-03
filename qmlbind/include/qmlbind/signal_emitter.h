#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \class qmlbind_signal_emitter
 * \brief a helper class to emit signals from C objects.
 *
 * Its methods are defined in `signal_emitter.h`.
 */

/*! \file signal_emitter.h
 * \brief Contains all methods defined on `qmlbind_signal_emitter`.
 */

/*!
 * \brief emits the signal `signal_name` with `argc` arguments in `argv`.
 */
QMLBIND_API void qmlbind_signal_emitter_emit(qmlbind_signal_emitter *self,
                                             const char *signal_name, int argc, const qmlbind_value *const *argv);

/*!
 * \brief returns this signal emitter's associated engine.
 *
 * Does not transfer ownership of the returned engine.
 */
QMLBIND_API qmlbind_engine *qmlbind_signal_emitter_get_engine(const qmlbind_signal_emitter *self);

/*!
 * \brief destroys this signal emitter.
 */
QMLBIND_API void qmlbind_signal_emitter_release(qmlbind_signal_emitter *self);

#ifdef __cplusplus
}
#endif
