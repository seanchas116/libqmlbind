#pragma once

#include "qmlbind_global.h"

#ifdef __cplusplus
extern "C" {
#endif


/*! \class qmlbind_component
 * \brief encapsulates a QML component definition.
 *
 * Components are reusable, encapsulated QML types with well-defined interfaces.
 *
 * Its methods are defined in \ref component.h.
 *
 * You can find a simple usage example in `examples/create_component_get_property`.
 *
 * libqmlbind's equivalent of [QQmlComponent](https://doc.qt.io/qt-5/qqmlcomponent.html).
 */

/*! \file component.h
 * \brief Contains all methods defined on `qmlbind_component`.
 */


/*!
 * \brief Create a new `qmlbind_component` with no data.
 *
 * Use `qmlbind_component_set_data` or `qmlbind_component_load_path` to load QML code into the component.
 *
 * libqmlbind's equivalent of [QQmlComponent::QQmlComponent](https://doc.qt.io/qt-5/qqmlcomponent.html#QQmlComponent).
 */
QMLBIND_API qmlbind_component *qmlbind_component_new(qmlbind_engine *engine);

/*!
 * \brief Destroys the `qmlbind_component`.
 *
 * libqmlbind's equivalent of [QQmlComponent::~QQmlComponent](https://doc.qt.io/qt-5/qqmlcomponent.html#dtor.QQmlComponent).
 */
QMLBIND_API void qmlbind_component_release(qmlbind_component *self);

/*!
 * \brief Sets the `qmlbind_component` to use the QML code loaded from the provided file path.
 *
 * libqmlbind's equivalent of [QQmlComponent::loadUrl](https://doc.qt.io/qt-5/qqmlcomponent.html#loadUrl)
 * using [QUrl::fromLocalFile](https://doc.qt.io/qt-5/qurl.html#fromLocalFile) for path parsing.
 */
QMLBIND_API void qmlbind_component_load_path(qmlbind_component *self, const char *path);

/*!
 * Sets the `qmlbind_component` to use the given QML `data`.
 *
 * If `url` is provided, it is used to set the component name and to provide a base path for items resolved by this
 * component.
 *
 * libqmlbind's equivalent of [QQmlComponent::setData](https://doc.qt.io/qt-5/qqmlcomponent.html#setData)
 * using [QUrl::fromLocalFile](https://doc.qt.io/qt-5/qurl.html#fromLocalFile) for path parsing.
 */
QMLBIND_API void qmlbind_component_set_data(qmlbind_component *self, const char *data, const char *path);

/*!
 * \brief Returns a human-readable description of any error.
 *
 * The string includes the file, location, and description of each error. If multiple errors are present, they are
 * separated by a newline character.
 *
 * The ownership of the returned string is transferred to the caller.
 *
 * If no errors are present, an nullptr is returned.
 *
 * libqmlbind's equivalent of [qtqml-component's errorString](http://doc.qt.io/qt-5/qml-qtqml-component.html#errorString-method)
 */
QMLBIND_API qmlbind_string *qmlbind_component_get_error_string(qmlbind_component *self);

/*!
 * \brief Create an object instance from this component. Returns a nullptr if creation failed.
 *
 * All instances will be created in the `qmlbind_engine`'s root context.
 *
 * The ownership of the returned object instance is transferred to the caller.
 *
 * libqmlbind's equivalent of [QQmlComponent::create](https://doc.qt.io/qt-5/qqmlcomponent.html#create).
 */
QMLBIND_API qmlbind_value *qmlbind_component_create(qmlbind_component *self);

#ifdef __cplusplus
}
#endif
