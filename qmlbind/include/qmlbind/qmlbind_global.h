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

#include <memory>

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
class MetaClass;
class SignalEmitter;

}

typedef QApplication qmlbind_application;

typedef QmlBind::Engine qmlbind_engine;
typedef QQmlComponent qmlbind_component;
typedef QPluginLoader qmlbind_plugin;

typedef QJSValue qmlbind_value;
typedef QJSValueIterator qmlbind_iterator;
typedef QByteArray qmlbind_string;

typedef QmlBind::MetaClass qmlbind_metaclass;
typedef QmlBind::SignalEmitter qmlbind_signal_emitter;

#else

typedef struct qmlbind_application {} qmlbind_application;

typedef struct qmlbind_engine {} qmlbind_engine;
typedef struct qmlbind_component {} qmlbind_component;
typedef struct qmlbind_plugin {} qmlbind_plugin;

typedef struct qmlbind_value {} qmlbind_value;
typedef struct qmlbind_iterator {} qmlbind_iterator;
typedef struct qmlbind_string {} qmlbind_string;

typedef struct qmlbind_metaclass {} qmlbind_metaclass;
typedef struct qmlbind_signal_emitter {} qmlbind_signal_emitter;

#endif

/*!
 * \defgroup client_interface_module client_interface
 * \brief all types in libqmlbind which are not implemented by libqmlbind but by the client using it.
 */

/** \addtogroup client_interface_module
 * @{
 */

/*!
 * \brief an opaque struct to represent a client-side object exposed to the metaobject system to libqmlbind.
 *
 * In the client's implementation of `qmlbind_client_callbacks`' `new_object()`, you need to return a
 * `qmlbind_client_object` pointer, which is then given back to you as `object` parameter in `call_method()`,
 * `get_property()` and `set_property()`.  With the `qmlbind_client_callbacks`, `qmlbind_client_object`s can be
 * created, used and deleted from QML.
 *
 * A `qmlbind_client_object` therefore is the rough equivalent of an instance of a
 * [QObject](http://doc.qt.io/qt-5/qobject.html#QObject) in code using libqmlbind.
 *
 * See `qmlbind_engine_new_wrapper()` to create new `qmlbind_value` wrappers for a `qmlbind_client_object`, and
 * `qmlbind_value_get_qmlbind_client_object()` to get the wrapped `qmlbind_client_object` back.
 */
typedef struct qmlbind_client_object {} qmlbind_client_object;

/*!
 * \brief an opaque struct to represent a client-side class object (a.k.a. metaclass) to libqmlbind.
 *
 * This is intended to be used in languages where classes are first-class objects, i.e. that have the concept of a class
 * object with which you can generically construct new objects. Examples are python's `type` class or ruby's `Class`
 * class. If you have this feautre, you can implement generic `qmlbind_client_callbacks` for all classes.
 *
 * In `qmlbind_exporter_new()`, a `qmlbind_client_class` pointer can be provided which is forwarded to
 * `qmlbind_client_callbacks`' `new_object()` for that purpose. You could use it to transfer an arbitrary object,
 * though.
 *
 * In other languages, you can ignore this and implement multiple `qmlbind_client_callbacks`.
 *
 * A `qmlbind_client_class` is the rough equivalent of a class inheriting
 * [QObject](http://doc.qt.io/qt-5/qobject.html#QObject) located in code using libqmlbind.
 */
typedef struct qmlbind_client_class {} qmlbind_client_class;


/*!
 * \brief encapsulates client-side functions that are used from QML for C object creation, destruction,
 * method calls and property modification.
 *
 * Those functions need to be implemented by libqmlbind's users for `qmlbind_client_object`s they want to expose to QML.
 *
 * This struct is needed to construct new `qmlbind_exporter`s. All function pointers need to be defined, a nullptr is
 * not a valid value here.
 */
typedef struct qmlbind_client_callbacks {
    /*!
     * \brief creates a new `qmlbind_client_object` to be used in QML.
     *
     * `qmlbind_client_callbacks` hands over the `qmlbind_client_object` returned from this function as `object` to
     * `call_method()`, `get_property()` and `set_property()`.
     *
     * \param classRef the `qmlbind_client_class` value that was given to `qmlbind_exporter_new`.
     * Does not transfer ownership.
     * \param signalEmitter should be stored in the returned object to be able to emit signals. Ownership is transfered.
     * \returns the newly-created object, transfering ownership to libqmlbind.
     */
    qmlbind_client_object* (*new_object)(qmlbind_client_class *classRef, qmlbind_signal_emitter *signalEmitter);

    /*!
     * \brief deletes a `qmlbind_client_object` that was created by `new_object`.
     */
    void (*delete_object)(qmlbind_client_object *object);

    /*!
     * \brief executes the `name` method defined on the `qmlbind_client_object`, with `argc` parameters in `argv`, and returns
     * the result.
     *
     * If the method does not return a value, `call_method()` should return `qmlbind_value_new_undefined()`.
     *
     * Ownership of the result must be transfered to the caller.
     *
     * Ownership of `engine` and `object` is not transfered.
     *
     * `engine` is intended to be used to create new objects or arrays.
     */
    qmlbind_value* (*call_method)(qmlbind_engine *engine, qmlbind_client_object *object,
                                  const char *name, int argc, const qmlbind_value *const *argv);

    /*!
     * \brief returns the value of the `name` property of the `object` C object.
     * Ownership must be transferred to the caller.
     *
     * In case the `name` property does not exist, you should return a `qmlbind_value_new_undefined()`.
     *
     * Ownership of `engine` and `object` is not transfered.
     *
     * `engine` is intended to be used to create new objects or arrays.
     */
    qmlbind_value* (*get_property)(qmlbind_engine *engine, qmlbind_client_object *object, const char *name);

    /*!
     * \brief sets the value of the `name` property to of the `object` C object to `value`.
     *
     * Ownership of `engine` and `object` is not transfered.
     *
     * `engine` is intended to be used to create new objects or arrays.
     */
    void (*set_property)(qmlbind_engine *engine, qmlbind_client_object *object, const char *name, const qmlbind_value *value);

} qmlbind_client_callbacks;

/** @} */
