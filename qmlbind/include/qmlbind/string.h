#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup string_module qmlbind_string
 * \brief Acts as string wrapper for libqmlbind's api.
 *
 * This is equivalent to a QString stored as a [QByteArray](https://doc.qt.io/qt-5/qbytearray.html),
 * encoded with [QString::toUtf8](https://doc.qt.io/qt-5/qstring.html#fromUtf8).
 */

/** \addtogroup string_module
 *  @{
 */

/*! \struct qmlbind_string
 * \brief an opaque struct mainly used as `self` argument in the methods defined in \ref string_module.
 */

/*! \file string.h
 * \brief Contains all methods defined on \ref string_module.
 */


/*!
 * \brief Returns a pointer to the chars stored in the `qmlbind_string`.
 *
 * The pointer can be used to access the chars that compose the string. The data is '\0'-terminated.
 * The pointer remains valid as long as the string isn't destroyed.
 *
 * libqmlbind's equivalent of [QByteArray::constData](https://doc.qt.io/qt-5/qbytearray.html#constData)
 */
QMLBIND_API const char *qmlbind_string_get_chars(const qmlbind_string *self);

/*!
 * \brief Returns the number of chars in this string.
 *
 * The last byte in the string is at position `qmlbind_string_get_length() - 1`.
 * In addition, `qmlbind_string` ensures that the char at position `qmlbind_string_get_length()` is always '\0',
 * so that you can use the return value of `qmlbind_string_get_chars()` as argument to functions that expect
 * '\0'-terminated strings.
 *
 * libqmlbind's equivalent of [QByteArray::size](https://doc.qt.io/qt-5/qbytearray.html#size)
 */
QMLBIND_API int qmlbind_string_get_length(const qmlbind_string *self);

/*!
 * \brief Destroys the `qmlbind_string`.
 */
QMLBIND_API void qmlbind_string_release(qmlbind_string *self);

/** @}*/
#ifdef __cplusplus
}
#endif
