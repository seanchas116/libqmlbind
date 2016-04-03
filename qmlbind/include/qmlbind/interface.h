#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \class qmlbind_interface
 * \brief a wrapper around qmlbind_interface_handlers used to create new exporters.
 *
 * Its methods are defined in \ref interface.h.
 */

/*! \file interface.h
 * \brief Contains all methods defined on `qmlbind_interface`.
 */

/*!
 * \brief Creates a new `qmlbind_interface` wrapper.
 *
 * You can either create a single, generic one and pass that to every new \ref qmlbind_exporter_new, or create specific
 * ones for each exporter.
 */
QMLBIND_API qmlbind_interface *qmlbind_interface_new(
    qmlbind_interface_handlers handlers
);

/*!
 * \brief Destroys the `qmlbind_interface`.
 */
QMLBIND_API void qmlbind_interface_release(qmlbind_interface *interface);

#ifdef __cplusplus
}
#endif
