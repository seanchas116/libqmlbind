#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup metaclass_module qmlbind_metaclass
 * \brief Defines an object type for use in QML type system.
 *
 * It enables you to wrap client objects into a [QML object type](http://doc.qt.io/qt-5/qtqml-typesystem-objecttypes.html) and instantiate them in QML.
 * It is also possible to create wrappers as `qmlbind_value` in `qmlbind_engine_new_wrapper`.
 *
 * Internally, the `qmlbind_metaclass` creates a [QMetaObject](https://doc.qt.io/qt-5/qmetaobject.html) for the wrapper Qt objects.
 *
 * libqmlbind's rough equivalent of [Meta-Object Compiler](http://doc.qt.io/qt-5/moc.html).
 */

/** \addtogroup metaclass_module
 *  @{
 */

/*! \struct qmlbind_metaclass
 * \brief an opaque struct mainly used as `self` argument in the methods defined in \ref metaclass_module.
 */

/*! \file metaclass.h
 * \brief Contains all methods defined on `qmlbind_metaclass`.
 */

/*!
 * \brief Creates a new `qmlbind_metaclass`.
 *
 * \param classObject will be given as parameter to the `new_object` function of the provided
 * `qmlbind_client_callbacks`. You can use it to hand over the equivalent of class objects in your language to
 * implement a generic `new_object` function. If you don't need it, just hand over a nullpointer. This function does not
 * take ownership of the classObject, but it still needs to be valid for as long as new objects are created (i.e. the
 * whole application lifetime).
 *
 * \param className is used for registering this metaclass in the metaobject system.
 *
 * \param callbacks is used to create, use and delete instances of the metaobject to build.
 * You can either create a single, generic one and pass that to every new \ref qmlbind_metaclass_new, or create specific
 * ones for each metaclass.
 */
QMLBIND_API qmlbind_metaclass *qmlbind_metaclass_new(
    qmlbind_client_class *classObject,
    const char *className,
    qmlbind_client_callbacks callbacks
);

/*!
 * \brief Destroys the `qmlbind_metaclass`.
 */
QMLBIND_API void qmlbind_metaclass_release(qmlbind_metaclass *self);

/*!
 * \brief Adds a new method `name` for the resulting metaobject with `arity` number of parameters.
 *
 * Such methods can either directly be called from QML or be used as QML signal handlers, as described in [Signal and
 * Handler Event System](https://doc.qt.io/qt-5/qtqml-syntax-signals.html).
 *
 * libqmlbind's equivalent of [QObject's Q_INVOKABLE](https://doc.qt.io/qt-5/qobject.html#Q_INVOKABLE).
 */
QMLBIND_API void qmlbind_metaclass_add_method(
    qmlbind_metaclass *self,
    const char *name,
    int arity
);

/*!
 * \brief Adds a new signal `name` for the resulting metaobject with `arity` number of parameters.
 *
 * `params` specifies the name of the signal parameters and has to be of length `arity`, which means you have to specify
 * a name for each parameter.
 *
 * Such signals can be received by QML signal handlers, as described in
 * [Signal and Handler Event System](https://doc.qt.io/qt-5/qtqml-syntax-signals.html).
 */
QMLBIND_API void qmlbind_metaclass_add_signal(
    qmlbind_metaclass *self,
    const char *name,
    int arity,
    const char *const *params
);

/*!
 * \brief Adds a new property `name` for the resulting metaobject, which should emit `notifierSignal` on changes.
 *
 * Properties in libqmlbind are always readable and writable from QML code, and must have a notifierSignal for changes.
 * Other possibilities, like a read-only or a constant proprerty, are not yet explicitly supported. But of course you
 * could can use a signal that is never emitted and refrain from writing to the properties…
 *
 * Read & write operations will be executed through
 * `qmlbind_client_callbacks`' `read_property` & `write_property` functions.
 *
 * \param notifierSignal has to be a valid signal name, which means neither a nullptr nor an empty string. The
 * signal should be added with `qmlbind_metaclass_add_signal` in advance, or else a warning will be issued.
 * Notify signals are usually named `<propertyname>Changed` in Qt.
 *
 * libqmlbind's equivalent of [Q_PROPERTY](https://doc.qt.io/qt-5/properties.html), always using READ, WRITE and NOTIFY.
 */
QMLBIND_API void qmlbind_metaclass_add_property(
    qmlbind_metaclass *self,
    const char *name,
    const char *notifierSignal
);

/*!
 * \brief exposes the `metaclass` as `qmlName` component to QML.
 *
 * `uri`, `versionMajor` and `versionMinor` is the package uri and version under which this `metaclass` is made
 * available to QML. After calling this function, you can import the component as:
 *
 * ```
 * import <uri> <versionMajor>.<versionMinor>
 * ```
 *
 * After registering, metaclass changes such as method addition will not be reflected in the QML type system.
 *
 * This is libqmlbind's rough equivalent of
 * [QQmlEngine::registerType](https://doc.qt.io/qt-5/qqmlengine.html#qmlRegisterType).
 */
QMLBIND_API int qmlbind_metaclass_register(
    qmlbind_metaclass *self,
    const char *uri,
    int versionMajor, int versionMinor,
    const char *qmlName
);

/** @}*/
#ifdef __cplusplus
}
#endif
