#pragma once

# if defined(_WIN32) || defined(_WIN64)
#   ifdef QMLBIND_LIBRARY
#     define QMLBIND_API __declspec(dllexport)
#   else
#     define QMLBIND_API __declspec(dllimport)
#   endif
# else
#   define QMLBIND_API
# endif

/*!
 * \file qmlbind_global.h
 * \brief Contains all struct definitions of libqmlbind.
 *
 * Functions using these structs as arguments are defined in all other header files.
 */

// use the real declarations if libqmlbind is being built as a library (which means QMLBIND_LIBRARY is defined),
// but use opaque structs if this is another project and only libqmlbind's header files are included.
#ifdef QMLBIND_LIBRARY

template <typename T> class QSharedPointer;
class QApplication;
class QQmlComponent;
class QJSValue;
class QJSValueIterator;
class QByteArray;
class QPluginLoader;

namespace QmlBind {

class Engine;
class Interface;
class MetaObject;
class Exporter;
class SignalEmitter;

}

typedef QApplication qmlbind_application;

typedef QmlBind::Engine qmlbind_engine;
typedef QQmlComponent qmlbind_component;
typedef QPluginLoader qmlbind_plugin;

typedef QJSValue qmlbind_value;
typedef QJSValueIterator qmlbind_iterator;
typedef QByteArray qmlbind_string;

// Use shared pointer for widely referenced classes
typedef QSharedPointer<QmlBind::Interface> qmlbind_interface;
typedef QSharedPointer<QmlBind::MetaObject> qmlbind_metaobject;
typedef QSharedPointer<QmlBind::Exporter> qmlbind_exporter;

typedef QmlBind::SignalEmitter qmlbind_signal_emitter;

#else

typedef struct qmlbind_application {} qmlbind_application;

typedef struct qmlbind_engine {} qmlbind_engine;
typedef struct qmlbind_component {} qmlbind_component;
typedef struct qmlbind_plugin {} qmlbind_plugin;

typedef struct qmlbind_value {} qmlbind_value;
typedef struct qmlbind_iterator {} qmlbind_iterator;
typedef struct qmlbind_string {} qmlbind_string;

typedef struct qmlbind_interface {} qmlbind_interface;
typedef struct qmlbind_metaobject {} qmlbind_metaobject;
typedef struct qmlbind_exporter {} qmlbind_exporter;

typedef struct qmlbind_signal_emitter {} qmlbind_signal_emitter;

#endif

/*!
 * \brief is a reference to an object or class back in the code calling libqmlbind's functions.
 *
 * In many cases, it can be seen as a pointer to the equivalents of QObjects in the calling code, with some wrapping
 * code around it to be used as a real QObject for QML.
 *
 * See `qmlbind_engine_new_wrapper()` to create new `qmlbind_value` wrappers for a `qmlbind_backref`, and
 * `qmlbind_value_get_backref()` to get back the objRef given to it on creation.
 *
 * In `qmlbind_exporter_new()`, it is used as classRef which is forwarded `qmlbind_interface_handlers`' `new_object()`.
 * In this case, it's a pointer to an arbitrary object in the calling code, intended to be used for a generic class
 * object, which you can use to create new `objRef`s returned by `new_object()`.
 */
typedef struct qmlbind_backref {} qmlbind_backref;


/*!
 * \brief encapsulates functions that are used from QML for C object creation & destruction,
 * method calls and property modification.
 *
 * Those functions need to be defined by libqmlbind's users.
 *
 * This struct is needed to construct new `qmlbind_interface`s. All function pointers need to be defined, a nullptr is
 * not a valid argument.
 */
typedef struct qmlbind_interface_handlers {
    /*!
     * \brief creates a new C object to be used in QML.
     *
     * `qmlbind_interface_handlers` hands over the `qmlbind_backref` returned from this function as `objRef` to
     * `call_method()`, `get_property()` and `set_property()`.
     *
     * \param classRef the `qmlbind_backref` that was given to `qmlbind_exporter_new`. Does not transfer ownership.
     * \param signalEmitter should be stored in the returned object to be able to emit signals. Ownership is transfered.
     * \returns the newly-created object, transfering ownership.
     */
    qmlbind_backref* (*new_object)(qmlbind_backref *classRef, qmlbind_signal_emitter *signalEmitter);

    /*!
     * \brief deletes a C object that was created by `new_object`.
     */
    void (*delete_object)(qmlbind_backref *objRef);

    /*!
     * \brief executes the `name` method defined on the `objRef` C object, with `argc` parameters in `argv`, and returns
     * the result.
     *
     * Ownership of the result must be transfered to the caller.
     *
     * Ownership of `engine` and `objRef` is not transfered.
     *
     * `engine` is intended to be used to create new objects or arrays.
     */
    qmlbind_value* (*call_method)(qmlbind_engine *engine, qmlbind_backref *objRef,
                                  const char *name, int argc, const qmlbind_value *const *argv);

    /*!
     * \brief returns the value of the `name` property of the `objRef` C object.
     * Ownership must be transferred to the caller.
     *
     * Ownership of `engine` and `objRef` is not transfered.
     *
     * `engine` is intended to be used to create new objects or arrays.
     */
    qmlbind_value* (*get_property)(qmlbind_engine *engine, qmlbind_backref *objRef, const char *name);

    /*!
     * \brief sets the value of the `name` property to of the `objRef` C object to `value`.
     *
     * Ownership of `engine` and `objRef` is not transfered.
     *
     * `engine` is intended to be used to create new objects or arrays.
     */
    void (*set_property)(qmlbind_engine *engine, qmlbind_backref *objRef, const char *name, const qmlbind_value *value);

} qmlbind_interface_handlers;
