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
typedef std::shared_ptr<QmlBind::Interface> qmlbind_interface;
typedef std::shared_ptr<QmlBind::MetaObject> qmlbind_metaobject;
typedef std::shared_ptr<QmlBind::Exporter> qmlbind_exporter;

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
 * \brief an opaque struct used to transfer objects exposed to the metaobject system between libqmlbind and its user.
 *
 * In `qmlbind_interface_handlers`' `new_object()`, you need to return a `qmlbind_client_object` pointer, which is then given
 * back to you as `object` parameter in `call_method()`, `get_property()` and `set_property()`.
 * With the `qmlbind_interface_handlers`, `qmlbind_client_object`s can be created, used and deleted from QML.
 *
 * A `qmlbind_client_object` therefore is the rough equivalent of an instance of a
 * [QObject](http://doc.qt.io/qt-5/qobject.html#QObject) in code using libqmlbind.
 *
 * See `qmlbind_engine_new_wrapper()` to create new `qmlbind_value` wrappers for a `qmlbind_client_object`, and
 * `qmlbind_value_get_qmlbind_client_object()` to get the wrapped `qmlbind_client_object` back.
 */
typedef struct qmlbind_client_object {} qmlbind_client_object;

/*!
 * \brief an opaque struct used to transfer class objects of classes exposed to the metaobject system between libqmlbind
 * and its user.
 *
 * This is intended to be used in languages that have the concept of a class object with which you can generically
 * construct new objects. With that, you can implement generic `qmlbind_interface_handlers` for all classes. In other
 * languages, you can ignore it and implement multiple `qmlbind_interface_handlers`.
 *
 * A `qmlbind_client_class` therefore is the rough equivalent of a
 * [QObject](http://doc.qt.io/qt-5/qobject.html#QObject) class in code using libqmlbind.
 *
 * In `qmlbind_exporter_new()`, a `qmlbind_client_class` pointer can be provided which is forwarded to
 * `qmlbind_interface_handlers`' `new_object()` for that purpose. You could use it to transfer an arbitrary object,
 * though.
 */
typedef struct qmlbind_client_class {} qmlbind_client_class;


/*!
 * \brief encapsulates functions that are used from QML for C object creation & destruction,
 * method calls and property modification.
 *
 * Those functions need to be defined by libqmlbind's users.
 *
 * This struct is needed to construct new `qmlbind_interface`s. All function pointers need to be defined, a nullptr is
 * not a valid value here.
 */
typedef struct qmlbind_interface_handlers {
    /*!
     * \brief creates a new C object to be used in QML.
     *
     * `qmlbind_interface_handlers` hands over the `qmlbind_client_object` returned from this function as `object` to
     * `call_method()`, `get_property()` and `set_property()`.
     *
     * \param classRef the `qmlbind_client_class` that was given to `qmlbind_exporter_new`. Does not transfer ownership.
     * \param signalEmitter should be stored in the returned object to be able to emit signals. Ownership is transfered.
     * \returns the newly-created object, transfering ownership.
     */
    qmlbind_client_object* (*new_object)(qmlbind_client_class *classRef, qmlbind_signal_emitter *signalEmitter);

    /*!
     * \brief deletes a C object that was created by `new_object`.
     */
    void (*delete_object)(qmlbind_client_object *object);

    /*!
     * \brief executes the `name` method defined on the `object` C object, with `argc` parameters in `argv`, and returns
     * the result.
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

} qmlbind_interface_handlers;
