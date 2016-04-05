#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup metaobject_module
 *  @{
 */

/*! \file register.h
 * \brief Contains the `qmlbind_register_type` function.
 */

/*!
 * \brief exposes the `metaobject` as `qmlName` component to QML.
 *
 * `uri`, `versionMajor` and `versionMinor` is the package uri and version under which this `metaobject` is made
 * available to QML. After calling this function, you can import the component as:
 *
 * ```
 * import <uri> <versionMajor>.<versionMinor>
 * ```
 *
 * This is libqmlbind's rough equivalent of
 * [QQmlEngine::registerType](https://doc.qt.io/qt-5/qqmlengine.html#qmlRegisterType).
 */
QMLBIND_API int qmlbind_register_type(
    const qmlbind_metaobject *metaobject,
    const char *uri,
    int versionMajor, int versionMinor,
    const char *qmlName
);

/** @}*/
#ifdef __cplusplus
}
#endif
