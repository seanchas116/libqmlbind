#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup exporter_module qmlbind_exporter
 * \brief provides a builder-style API for creating a new \ref metaobject_module .
 *
 * After adding all wanted methods, signals and properties, an exporter should be transformed into a \ref
 * `metaobject_module` by using `qmlbind_exporter_into_metaobject()`.
 */

/** \addtogroup exporter_module
 *  @{
 */

/*! \struct qmlbind_exporter
 * \brief an opaque struct mainly used as `self` argument in the methods defined in \ref exporter_module.
 */

/*! \file exporter.h
 * \brief Contains all methods defined on `qmlbind_exporter`.
 */

/*!
 * \brief Creates a new `qmlbind_exporter`.
 *
 * \param classObject will be given as parameter to the `new_object` function of the provided
 * `qmlbind_interface_handlers`. You can use it to hand over the equivalent of class objects in your language to
 * implement a generic `new_object` function. If you don't need it, just hand over a nullpointer. This function does not
 * take ownership of the classObject, but it still needs to be valid for as long as new objects are created (i.e. the
 * whole application lifetime).
 *
 * \param className is used for registering the metaobject created with this exporter in the metaobject system.
 *
 * \param interfaceHandlers is used to create, use and delete instances of the metaobject to build.
 * You can either create a single, generic one and pass that to every new \ref qmlbind_exporter_new, or create specific
 * ones for each exporter.
 */
QMLBIND_API qmlbind_exporter *qmlbind_exporter_new(
    qmlbind_client_class *classObject,
    const char *className,
    qmlbind_interface_handlers interfaceHandlers
);

/*!
 * \brief Finalizes this `qmlbind_exporter` and transforms it into a new `qmlbind_metaobject`.
 *
 * Takes ownership of the given `qmlbind_exporter`.
 * Because the calling code does not own the exporter anymore after this call, no new methods etc. can be added
 * afterwards.
 *
 * Ownership of the returned `qmlbind_metaobject` is transfered to the caller.
 */
QMLBIND_API qmlbind_metaobject *qmlbind_exporter_into_metaobject(qmlbind_exporter *self);

/*!
 * \brief Adds a new method `name` for the resulting metaobject with `arity` number of parameters.
 *
 * Such methods can either directly be called from QML or be used as QML signal handlers, as described in [Signal and
 * Handler Event System](https://doc.qt.io/qt-5/qtqml-syntax-signals.html).
 *
 * libqmlbind's equivalent of [QObject's Q_INVOKABLE](https://doc.qt.io/qt-5/qobject.html#Q_INVOKABLE).
 */
QMLBIND_API void qmlbind_exporter_add_method(
    qmlbind_exporter *self,
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
QMLBIND_API void qmlbind_exporter_add_signal(
    qmlbind_exporter *self,
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
 * `qmlbind_interface_handlers`' `read_property` & `write_property` functions.
 *
 * \param notifierSignal has to be a valid signal name, which means neither a nullptr nor an empty string. The
 * signal should be added with `qmlbind_exporter_add_signal` in advance, or else a warning will be issued.
 * Notify signals are usually named `<propertyname>Changed` in Qt.
 *
 * libqmlbind's equivalent of [Q_PROPERTY](https://doc.qt.io/qt-5/properties.html), always using READ, WRITE and NOTIFY.
 */
QMLBIND_API void qmlbind_exporter_add_property(
    qmlbind_exporter *self,
    const char *name,
    const char *notifierSignal
);

/** @}*/
#ifdef __cplusplus
}
#endif
