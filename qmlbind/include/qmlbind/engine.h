#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup engine_module qmlbind_engine
 * \brief Provides an environment for instantiating QML components.
 *
 * libqmlbind only supports creation of components in each engine's root context.
 *
 * libqmlbind's equivalent of [QQmlEngine](https://doc.qt.io/qt-5/qqmlengine.html).
 */

/** \addtogroup engine_module
 *  @{
 */

/*! \struct qmlbind_engine
 * \brief an opaque struct mainly used as `self` argument in the methods defined in \ref engine_module.
 */

/*! \file engine.h
 * \brief Contains all methods defined on \ref engine_module.
 */

/*!
 * \brief Create a new QQmlEngine.
 *
 * libqmlbind's equivalent of [QQmlEngine::QQmlEngine](https://doc.qt.io/qt-5/qqmlengine.html#QQmlEngine).
 */
QMLBIND_API qmlbind_engine *qmlbind_engine_new();

/*!
 * \brief Destroys the QQmlEngine.
 *
 * libqmlbind's equivalent of [QQmlEngine::~QQmlEngine](https://doc.qt.io/qt-5/qqmlengine.html#dtor.QQmlEngine)
 */
QMLBIND_API void qmlbind_engine_release(qmlbind_engine *self);

/*!
 * \brief Evaluates program, using lineNumber as the base line number, and returns the result of the evaluation.
 *
 * Transfers ownership of the returned qmlbind_value to the caller.
 *
 * The script code will be evaluated in the context of the global object.
 *
 * The evaluation of program can cause an exception in the engine; in this case the return value will be the exception
 * that was thrown (typically an error value) ; see \ref qmlbind_value_is_error.
 *
 * `lineNumber` is used to specify a starting line number for program;
 * `line number` information reported by the engine that pertains to this evaluation will be based on this argument.
 * For example, if program consists of two lines of code, and the statement on the second line causes a script
 * exception, the exception line number would be `lineNumber` plus one.
 *
 * When no starting line number is specified, line numbers will be 1-based.
 *
 * `fileName` is used for error reporting.
 * For example, in error objects the file name is accessible through the "fileName" property if it is provided with this
 * function.
 *
 * libqmlbind's equivalent of [QJSEngine::evaluate](https://doc.qt.io/qt-5/qjsengine.html#evaluate)
 */
QMLBIND_API qmlbind_value *qmlbind_engine_eval(
    qmlbind_engine *self,
    const char *str, const char *fileName, int lineNumber
);

/*!
 * \brief Returns this engine's Global Object.
 *
 * Transfers ownership of the returned qmlbind_value to the caller.
 *
 * By default, the Global Object contains the built-in objects that are part of ECMA-262, such as Math, Date and String.
 * Additionally, you can set properties of the Global Object to make your own extensions available to all script code.
 * Non-local variables in script code will be created as properties of the Global Object, as well as local variables in
 * global code.
 *
 * libqmlbind's equivalent of [QJSEngine::globalObject](https://doc.qt.io/qt-5/qjsengine.html#globalObject)
 */
QMLBIND_API qmlbind_value *qmlbind_engine_get_global_object(const qmlbind_engine *self);

/*!
 * \brief Creates a JavaScript object of class Object.
 *
 * The prototype of the created object will be the Object prototype object.
 *
 * Transfers ownership of the returned qmlbind_value to the caller.
 *
 * libqmlbind's equivalent of [QJSEngine::newObject](https://doc.qt.io/qt-5/qjsengine.html#newObject)
 */
QMLBIND_API qmlbind_value *qmlbind_engine_new_object(qmlbind_engine *self);

/*!
 * \brief Creates a JavaScript object of class Array with the given `length`.
 *
 * Transfers ownership of the returned qmlbind_value to the caller.
 *
 * libqmlbind's equivalent of [QJSEngine::newObject](https://doc.qt.io/qt-5/qjsengine.html#newArray)
 */
QMLBIND_API qmlbind_value *qmlbind_engine_new_array(qmlbind_engine *self, int length);

/*!
 * \brief Creates a JavaScript object that wraps the given `object`.
 *
 * This is intended to be used to expose `qmlbind_client_object` instances that were created by the client code directly
 * to QML via `qmlbind_value_set_properties()`, e.g. on the Global Object returned by
 * `qmlbind_engine_get_global_object()`. In that case, the metaclasses don't need to be registered via
 * `qmlbind_metaclass_register` and don't need to be created inside QML.
 *
 * If the `object` should be able to send signals, you must create a `qmlbind_signal_emitter` for it afterwards by
 * calling `qmlbind_signal_emitter_new()` with the returned value.
 *
 * Transfers ownership of the returned qmlbind_value to the caller.
 * Takes ownership of `object`.
 *
 * Signals and slots, properties and children of `object` are available as properties of the created `qmlbind_value`.
 *
 * If `object` is a null pointer, this function returns a null value.
 *
 * After creating a wrapper, metaclass changes such as method addition will not be reflected in the created wrapper.
 *
 * libqmlbind's equivalent of [QJSEngine::newQObject](https://doc.qt.io/qt-5/qjsengine.html#newQObject) plus the
 * additional wrapper logic to create a QObject for `object` with `metaclass`.
 */
QMLBIND_API qmlbind_value *qmlbind_engine_new_wrapper(
    qmlbind_engine *self,
    const qmlbind_metaclass *metaclass,
    qmlbind_client_object *object
);

/*!
 * \brief Adds path as a directory where the engine searches for installed modules in a URL-based directory structure.
 *
 * The path may be a local filesystem directory, a Qt Resource path (:/imports), a Qt Resource url (qrc:/imports) or a
 * URL.
 *
 * The path will be converted into canonical form before it is added to the import path list.
 *
 * libqmlbind's equivalent of [QQmlEngine::addImportPath](https://doc.qt.io/qt-5/qqmlengine.html#addImportPath).
 */
QMLBIND_API void qmlbind_engine_add_import_path(qmlbind_engine *self, const char *path);

/*!
 * \brief Runs the garbage collector.
 *
 * The garbage collector will attempt to reclaim memory by locating and disposing of objects that are no longer
 * reachable in the script environment.
 *
 * Normally you don't need to call this function; the garbage collector will automatically be invoked when the
 * `qmlbind_engine` decides that it's wise to do so (i.e. when a certain number of new objects have been created).
 * However, you can call this function to explicitly request that garbage collection should be performed as soon as
 * possible.
 *
 * libqmlbind's equivalent of [QJSEngine::collectGarbage](https://doc.qt.io/qt-5/qjsengine.html#collectGarbage).
 */
QMLBIND_API void qmlbind_engine_collect_garbage(qmlbind_engine *self);

/** @}*/
#ifdef __cplusplus
}
#endif
