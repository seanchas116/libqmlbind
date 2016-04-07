#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup metaobject_module qmlbind_metaobject
 * \brief contains all meta-information on an object.
 *
 * To create new `qmlbind_metaobject`s, create a new \ref exporter_module and use
 * the`qmlbind_exporter_into_metaobject()` function to transform it into a `qmlbind_metaobject`.
 *
 * libqmlbind's equivalent of [QMetaObject](https://doc.qt.io/qt-5/qmetaobject.html)
 */

/** \addtogroup metaobject_module
 *  @{
 */


/*! \struct qmlbind_metaobject
 * \brief an opaque struct mainly used as `self` argument in the methods defined in \ref metaobject_module.
 */

/*! \file metaobject.h
 * \brief Contains all methods defined on \ref metaobject_module.
 *
 */

/*!
 * \brief Creates a new `qmlbind_metaobject` as specified by the given `exporter`.
 *
 * The content of the `exporter` is copied, so it does not need to outlive this `qmlbind_metaobject` and should
 * be destroyed directly afterwards, as there is nothing left to do with it.
 */
QMLBIND_API qmlbind_metaobject *qmlbind_metaobject_new(
    const qmlbind_metaclass *metaclass
);

/*!
 * \brief Destroys this `qmlbind_metaobject`.
 */
QMLBIND_API void qmlbind_metaobject_release(qmlbind_metaobject *metaobject);

/** @}*/
#ifdef __cplusplus
}
#endif
