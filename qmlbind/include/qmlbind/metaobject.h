#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \class qmlbind_metaobject
 * \brief contains all meta-information on an object.
 *
 * Its methods are defined in \ref metaobject.h.
 *
 * libqmlbind's equivalent of [QMetaObject](https://doc.qt.io/qt-5/qmetaobject.html)
 */

/*! \file metaobject.h
 * \brief Contains all methods defined on `qmlbind_metaobject`.
 */

/*!
 * \brief Creates a new `qmlbind_metaobject` as specified by the given `exporter`.
 *
 * \param qmlbind_exporter is copied, so it does not need to outlive this `qmlbind_metaobject` and should
 * be destroyed directly afterwards, as there is nothing left to do with it.
 */
QMLBIND_API qmlbind_metaobject *qmlbind_metaobject_new(const qmlbind_exporter *exporter);

/*!
 * \brief Destroys this `qmlbind_metaobject`.
 */
QMLBIND_API void qmlbind_metaobject_release(qmlbind_metaobject *metaobject);

#ifdef __cplusplus
}
#endif
