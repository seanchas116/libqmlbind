#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup signal_emitter_module qmlbind_signal_emitter
 * \brief a helper class to emit signals from `qmlbind_client_object` C objects.
 */

/** \addtogroup signal_emitter_module
 *  @{
 */

/*! \struct qmlbind_signal_emitter
 * \brief an opaque struct mainly used as `self` argument in the methods defined in \ref signal_emitter_module.
 */

/*! \file signal_emitter.h
 * \brief Contains all methods defined on \ref signal_emitter_module.
 */

/*!
 * \brief Creates a new emitter that emits signals via the provided `wrapper`.
 *
 * Passing `qmlbind_value`s that are not wrappers, i.e. `qmlbind_value_is_wrapper()` returns false, is an error here.
 */
QMLBIND_API qmlbind_signal_emitter *qmlbind_signal_emitter_new(qmlbind_value *wrapper);

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

/** @}*/
#ifdef __cplusplus
}
#endif
