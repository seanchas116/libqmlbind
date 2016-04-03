#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \class qmlbind_iterator
 * \brief provides a Java-style iterator for the properties of `qmlbind_value`s.
 *
 * Its methods are defined in \ref iterator.h.
 *
 *
 * The `qmlbind_iterator` constructor takes a `qmlbind_value` as argument.
 * After construction, the iterator is located at the very beginning of the sequence of properties.
 * Here's how to iterate over all the properties of a `qmlbind_value`:
 *
 * ```
 * qmlbind_value *object;
 * ...
 * qmlbind_iterator it = qmlbind_iterator_new(object);
 * while (qmlbind_iterator_has_next(it)) {
 *    qmlbind_iterator_next(it);
 *    qmlbind_string *key = qmlbind_iterator_get_key(it);
 *    qmlbind_value *value = qmlbind_iterator_get_value(it);
 *    qmlbind_string *value_str = qmlbind_iterator_get_string(it);
 *    printf("%s: %s", qmlbind_string_get_chars(key), qmlbind_string_get_chars(value_str));
 *    qmlbind_string_release(key);
 *    qmlbind_string_release(value_str);
 *    qmlbind_value_release(value);
 * }
 * ```
 *
 * The `qmlbind_iterator_next()` advances the iterator. The `qmlbind_iterator_get_key()` and
 * `qmlbind_iterator_get_value()` functions return the name and value of the last item that was jumped over.
 *
 * Note that `qmlbind_iterator` only iterates over the `qmlbind_value`'s own properties; i.e. it does not follow the
 * prototype chain. You can use a loop like this to follow the prototype chain:
 *
 * ```
 * qmlbind_value *obj = ...; // the object to iterate over
 * while (qmlbind_value_is_object(obj)) {
 *     qmlbind_iterator *it = qmlbind_iterator_new(obj);
 *     while (qmlbind_iterator_has_next(it)) {
 *         qmlbind_iterator_next(it);
 *         qmlbind_string *key = qmlbind_iterator_get_key(it);
 *         printf("%s", qmlbind_iterator_get_chars(key));
 *         qmlbind_string_release(key);
 *     }
 *     qmlbind_value *prototype = qmlbind_value_get_prototype(obj);
 *     qmlbind_value_release(obj);
 *     obj = prototype;
 * }
 * ```
 *
 * libqmlbind's equivalent of [QJSValueIterator](https://doc.qt.io/qt-5/qjsvalueiterator.html).
 */

/*! \file iterator.h
 * \brief Contains all methods defined on `qmlbind_iterator`.
 */


/*!
 * \brief Constructs an iterator for traversing `object`.
 *
 * The iterator is set to be at the front of the sequence of properties (before the first property).
 *
 * libqmlbind's equivalent of
 * [QJSValueIterator::QJSValueIterator](https://doc.qt.io/qt-5/qjsvalueiterator.html#QJSValueIterator).
 */
QMLBIND_API qmlbind_iterator *qmlbind_iterator_new(const qmlbind_value *object);

/*!
 * \brief Destroys this `qmlbind_iterator`.
 */
QMLBIND_API void qmlbind_iterator_release(qmlbind_iterator *self);

/*!
 * \brief Returns the name of the last property that was jumped over using `qmlbind_iterator_next()`.
 *
 * Ownership of the returned string is transfered to the caller.
 *
 * libqmlbind's equivalent of [QJSValueIterator::name()](https://doc.qt.io/qt-5/qjsvalueiterator.html#name).
 */
QMLBIND_API qmlbind_string *qmlbind_iterator_get_key(const qmlbind_iterator *self);

/*!
 * \brief Returns the value of the last property that was jumped over using `qmlbind_iterator_next()`.
 *
 * Ownership of the returned value is transfered to the caller.
 *
 * libqmlbind's equivalent of [QJSValueIterator::value()](https://doc.qt.io/qt-5/qjsvalueiterator.html#value).
 */
QMLBIND_API qmlbind_value *qmlbind_iterator_get_value(const qmlbind_iterator *self);

/*!
 * \brief Advances the iterator by one position.
 *
 * Returns 1 if there was at least one item ahead of the iterator
 * (i.e. the iterator was not already at the back of the property sequence); otherwise returns 0.
 *
 * libqmlbind's equivalent of [QJSValueIterator::next()](https://doc.qt.io/qt-5/qjsvalueiterator.html#next).
 */
QMLBIND_API void qmlbind_iterator_next(qmlbind_iterator *self);

/*!
 * \brief Returns 1 if there is at least one item ahead of the iterator (i.e. the iterator is not at the back of the
 * property sequence); otherwise returns 0.
 *
 * libqmlbind's equivalent of [QJSValueIterator::hasNext()](https://doc.qt.io/qt-5/qjsvalueiterator.html#hasNext).
 */
QMLBIND_API int qmlbind_iterator_has_next(const qmlbind_iterator *self);

#ifdef __cplusplus
}
#endif
