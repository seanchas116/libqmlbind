#pragma once
#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \class qmlbind_exporter
 * \brief provides a builder-style API for creating new `qmlbind_metaobject`s.
 *
 * Its methods are defined in \ref exporter.h.
 */

/*! \file exporter.h
 * \brief Contains all methods defined on `qmlbind_exporter`.
 */

/*!
 * \brief Creates a new `qmlbind_exporter`.
 *
 * \param classRef will be given as parameter to the `new_object` function of the interface. You can use it to hand over
 * the equivalent of class objects in your language to implement a generic `new_object` function. If you don't need it,
 * just hand over a nullpointer. This function does not take ownership of the classRef, but it still needs to be valid
 * for as long as new objects are created (i.e. the whole application lifetime).
 *
 * \param className is used for registering the metaobject created with this exporter in the metaobject system.
 *
 * \param qmlbind_interface is copied, so it does not need to outlive `qmlbind_exporter`s created with it and can
 * be destroyed as soon as all exporters are created.
 *
 */
QMLBIND_API qmlbind_exporter *qmlbind_exporter_new(
    qmlbind_backref *classRef,
    const char *className,
    const qmlbind_interface *interface
);

/*!
 * \brief Destroys this `qmlbind_exporter`.
 */
QMLBIND_API void qmlbind_exporter_release(qmlbind_exporter *exporter);

/*!
 * \brief Adds a new method `name` for the resulting metaobject with `arity` number of parameters.
 *
 * Such methods can either directly be called from QML or be used as QML signal handlers, as described in [Signal and
 * Handler Event System](https://doc.qt.io/qt-5/qtqml-syntax-signals.html).
 *
 * libqmlbind's equivalent of [QObject's Q_INVOKABLE](https://doc.qt.io/qt-5/qobject.html#Q_INVOKABLE).
 */
QMLBIND_API void qmlbind_exporter_add_method(
    qmlbind_exporter *exporter,
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
    qmlbind_exporter *exporter,
    const char *name,
    int arity,
    const char **params
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
 * \param notifySignal has to be a valid signal name, which means neither a nullptr nor an empty string. The
 * signal should be added with `qmlbind_exporter_add_signal` in advance, or else a warning will be issued.
 * Notify signals are usually named `<propertyname>Changed` in Qt.
 *
 * libqmlbind's equivalent of [Q_PROPERTY](https://doc.qt.io/qt-5/properties.html), always using READ, WRITE and NOTIFY.
 */
QMLBIND_API void qmlbind_exporter_add_property(
    qmlbind_exporter *exporter,
    const char *name,
    const char *notifierSignal
);

#ifdef __cplusplus
}
#endif
