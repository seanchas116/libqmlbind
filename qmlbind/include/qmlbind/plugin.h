#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \class qmlbind_plugin
 * \brief loads a plugin at run-time.
 *
 * Its methods are defined in \ref plugin.h.
 *
 * `qmlbind_plugin` provides access to a Qt plugin. A Qt plugin is stored in a shared library (a DLL).
 * `qmlbind_plugin` checks that a plugin is linked against the same version of Qt as the application.
 *
 * An instance of a `qmlbind_plugin` object operates on a single shared library file, which we call a plugin. It
 * provides access to the functionality in the plugin in a platform-independent way. Pass the filename of the plugin to
 * load to `qmlbind_plugin_new()`.
 *
 * Multiple instances of `qmlbind_plugin` can be used to access the same physical plugin.
 *
 * Once loaded, plugins remain in memory until all the application terminates, as `libqmlbind` does not currently support
 * unloading. Therefore, the root component will never be deleted as long as the application runs.
 *
 * See [How to Create Qt Plugins](https://doc.qt.io/qt-5/plugins-howto.html) for more information about how to make your
 * application extensible through plugins.
 *
 * Note that the `qmlbind_plugin` cannot be used if your application is statically linked against Qt. In this case, you
 * will also have to link to plugins statically.
 *
 * See also the [Plug & Paint Example](https://doc.qt.io/qt-5/qtwidgets-tools-plugandpaint-example.html).
 *
 * libqmlbind's equivalent of [QPluginLoader](https://doc.qt.io/qt-5/qpluginloader.html).
 */

/*! \file plugin.h
 * \brief Contains all methods defined on `qmlbind_plugin`.
 */


/*!
 * \brief Constructs a plugin loader that will load the plugin specified by `filename`.
 *
 * To be loadable, the file's suffix must be a valid suffix for a loadable library in accordance with the platform, e.g.
 * .so on Unix, .dylib on OS X and iOS, and .dll on Windows.
 *
 * libqmlbind's equivalent of
 * [QPluginLoader::QPluginLoader(const QString& filename)](https://doc.qt.io/qt-5/qpluginloader.html#QPluginLoader-1).
 */
QMLBIND_API qmlbind_plugin *qmlbind_plugin_new(const char *filename);

/*!
 * \brief Destroys this `qmlbind_plugin`.
 */
QMLBIND_API void qmlbind_plugin_release(qmlbind_plugin *self);

/*!
 * \brief Returns a text string with the description of the last error that occurred.
 *
 * Ownership of the string is transfered to the caller.
 */
QMLBIND_API qmlbind_string *qmlbind_plugin_get_error_string(qmlbind_plugin *self);

/*!
 * \brief Returns the root component object of the plugin. The plugin is loaded if necessary.
 *
 * The function returns 0 if the plugin could not be loaded or if the root component object could not be instantiated.
 *
 * Ownership of the returned value is transfered to the caller.
 *
 * If the root component object was destroyed, calling this function creates a new instance.
 *
 * The root component, returned by this function, is not deleted when the `qmlbind_plugin` is destroyed. You'd need to
 * unload it, which is not supported by `libqmlbind` currently.
 *
 * libqmlbind's equivalent of [QPluginLoader::instance()](https://doc.qt.io/qt-5/qpluginloader.html#instance)
 */
QMLBIND_API qmlbind_value *qmlbind_plugin_get_instance(qmlbind_plugin *self, qmlbind_engine *engine);

#ifdef __cplusplus
}
#endif
