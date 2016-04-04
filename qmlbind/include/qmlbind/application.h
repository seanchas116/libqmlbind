#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif

/*! \class qmlbind_application
 * \brief manages the GUI application's control flow and main settings.
 *
 * Its methods are defined in \ref application.h.
 *
 * libqmlbind's equivalent of [QApplication](https://doc.qt.io/qt-5/qapplication.html).
 */

/*! \file application.h
 * \brief Contains all methods defined on `qmlbind_application`.
 */


/*!
 * \brief Initializes the window system and constructs an application object
 * with `argc` command line arguments in * `argv`.
 *
 * Does not take ownership of the passed `argv`.
 * Only one application object should be created.
 *
 * libqmlbind's equivalent of [QApplication::QApplication](https://doc.qt.io/qt-5/qapplication.html#QApplication).
 */
QMLBIND_API qmlbind_application *qmlbind_application_new(int argc, const char *const *argv);

/*!
 * \brief Returns a pointer to the application's QApplication instance.
 *
 * If no instance has been allocated, null is returned.
 *
 * Does not transer ownership of the qmlbind_application to the caller.
 *
 * libqmlbind's equivalent of [QApplication's qApp macro](https://doc.qt.io/qt-5/qapplication.html#qApp).
 */
QMLBIND_API qmlbind_application *qmlbind_application_instance(void);

/*!
 * \brief Cleans up any window system resources that were allocated by this application.
 *
 * Sets the global variable qApp to 0.
 * libqmlbind's equivalent of [QApplication::~QApplication](https://doc.qt.io/qt-5/qapplication.html#dtor.QApplication).
 */
QMLBIND_API void qmlbind_application_release(qmlbind_application *self);

/*!
 * \brief Enters the main event loop and waits until exit() is called,
 * then returns the value that was set to exit() (which is 0 if exit() is called via quit()).
 *
 * libqmlbind's equivalent of [QApplication::exec](https://doc.qt.io/qt-5/qapplication.html#exec).
 */
QMLBIND_API int qmlbind_application_exec(qmlbind_application *self);

/*!
 * \brief Processes all pending events for the calling thread until there are no more events to process.
 *
 * You can call this function occasionally when your program is busy performing a long operation (e.g. copying a file).
 * This also cleans up deferred deletes.
 *
 * libqmlbind's equivalent of [QCoreApplication::processEvents](https://doc.qt.io/qt-5/qcoreapplication.html#processEvents)
 * and [QCoreApplication::sendPostedEvents](https://doc.qt.io/qt-5/qcoreapplication.html#sendPostedEvents) for
 * processing deferred deletes.
 */
QMLBIND_API void qmlbind_process_events();

/*!
 * \brief Adds `callback` as to an event queue and returns immediately.
 *
 * This takes ownership from `data` and transfers it to `callback` later.
 * Therefore, `data` has to be created on the heap and freed by `callback` at the end of the function.
 *
 * Enqueuing is done via [QCoreApplication::postEvent](https://doc.qt.io/qt-5/qcoreapplication.html#postEvent).
 */
QMLBIND_API void qmlbind_next_tick(void (*callback)(void *), void *data);

#ifdef __cplusplus
}
#endif
