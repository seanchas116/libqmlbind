#pragma once
#include "qmlbind_global.h"
#include <time.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup value_module qmlbind_value
 * \brief acts as a container for Qt/JavaScript data types.
 *
 * `qmlbind_value` supports the types defined in the
 * [ECMA-262 standard](https://www.ecma-international.org/publications/standards/Ecma-262.htm):
 * The primitive types, which are Undefined, Null, Boolean, Number, and String; and the Object type.
 *
 * Additionally, built-in support is provided for wrappers around C objects exposed to the metaobject system.
 *
 * For the object-based types, use the `qmlbind_engine_new_T()` functions, e.g. `qmlbind_engine_new_object()` to create
 * objects of the desired type.
 * For the primitive types, use one of the `qmlbind_value` constructors.
 *
 * The methods named `qmlbind_value_is_T()` (e.g. `qmlbind_value_is_bool()`, `qmlbind_value_is_undefined()`) can be used
 * to test if a value is of a certain type.
 *
 * The methods named `qmlbind_value_get_T()` (e.g. `qmlbind_value_get_bool()`, `qmlbind_value_get_string()`) can be used
 * to convert a `qmlbind_value` to another type.
 *
 * Object values have zero or more properties which are themselves `qmlbind_value`s.
 * Use `qmlbind_value_set_property()` to set a property of an
 * object, and call `qmlbind_value_get_property()` to retrieve the value of a property.
 *
 * ```
 * qmlbind_engine *myEngine = qmlbind_engine_new();
 * qmlbind_value *myObject = qmlbind_engine_new_object(myEngine);
 * qmlbind_value *myOtherObject = qmlbind_engine_new_object(myEngine);
 *
 * qmlbind_value_set_property(myObject, "myChild", myOtherObject);
 * qmlbind_value *name = qmlbind_value_new_string_cstr("John Doe");
 * qmlbind_value_set_property(myObject, "name", name);
 *
 * qmlbind_value_release(name);
 * qmlbind_value_release(myOtherObject);
 * ```
 *
 * If you want to iterate over the properties of a script object, use the `qmlbind_iterator` class.
 *
 * Object values have an internal prototype property, which can be accessed with `qmlbind_value_get_prototype()` and
 * `qmlbind_value_set_prototype()`.
 *
 * Function objects (objects for which `qmlbind_value_is_function()` returns true) can be invoked by calling
 * `qmlbind_value_call()`.
 * Constructor functions can be used to construct new objects by calling `qmlbind_value_call_constructor()`.
 *
 * Use `qmlbind_value_is_equal()` or `qmlbind_value_is_identical()` to compare a `qmlbind_value`s to another.
 *
 * Note that a `qmlbind_value` for which `qmlbind_value_is_object()` is true only carries a reference to an actual
 * object; copying the `qmlbind_value` will only copy the object reference, not the object itself.
 * If you want to clone an object (i.e. copy an object's properties to another object),
 * you can do so with the help of a for-in statement in QML script code, or `qmlbind_iterator` in C.
 *
 * libqmlbind's equivalent of a [QJSValue](https://doc.qt.io/qt-5/qjsvalue.html).
 *
 */

/** \addtogroup value_module
 *  @{
 */

/*! \struct qmlbind_value
 * \brief an opaque struct mainly used as `self` argument in the methods defined in \ref value_module.
 */

/*! \file value.h
 * \brief Contains all methods defined on \ref value_module.
 */


/*!
 * \brief Constructs a new undefined `qmlbind_value`.
 *
 * libqmlbind's equivalent of [QJSValue::QJSValue](https://doc.qt.io/qt-5/qjsvalue.html#QJSValue)
 * called with [QJSValue::UndefinedValue](https://doc.qt.io/qt-5/qjsvalue.html#SpecialValue-enum).
 */
QMLBIND_API qmlbind_value *qmlbind_value_new_undefined();

/*!
 * \brief Constructs a new null `qmlbind_value`.
 *
 * libqmlbind's equivalent of [QJSValue::QJSValue](https://doc.qt.io/qt-5/qjsvalue.html#QJSValue)
 * called with [QJSValue::NullValue](https://doc.qt.io/qt-5/qjsvalue.html#SpecialValue-enum).
 */
QMLBIND_API qmlbind_value *qmlbind_value_new_null();

/*!
 * \brief Destroys this `qmlbind_value`.
 */
QMLBIND_API void qmlbind_value_release(qmlbind_value *self);

/*!
 * \brief Constructs a new `qmlbind_value` that is a copy of `other`.
 *
 * Note that if other is an object (i.e., `qmlbind_value_is_object()` would return true), then only a reference to the
 * underlying object is copied into the new script value (i.e., the object itself is not copied).
 *
 * libqmlbind's equivalent of [QJSValue::QJSValue](https://doc.qt.io/qt-5/qjsvalue.html#QJSValue-1)
 * called as copy-constructor.
 */
QMLBIND_API qmlbind_value *qmlbind_value_clone(const qmlbind_value *other);

/*!
 * \brief Returns true if `value1` is equal to `value2`, otherwise returns false.
 *
 * The comparison follows the behavior described in
 * [ECMA-262](http://www.ecma-international.org/publications/standards/Ecma-262.htm) section 11.9.3,
 * "The Abstract Equality Comparison Algorithm".
 *
 * This function can return true even if the type of this `qmlbind_value` is different from the type of the other value;
 * i.e.  the comparison is not strict. For example, comparing the number 9 to the string "9" returns true; comparing an
 * undefined value to a null value returns true; comparing a Number object whose primitive value is 6 to a String object
 * whose primitive value is "6" returns true; and comparing the number 1 to the boolean value true returns true. If you
 * want to perform a comparison without such implicit value conversion, use `qmlbind_value_is_identical()`.
 *
 * Note that if `value1` or `value2` are objects, calling this function has side effects on the script
 * engine, since the engine will call the object's valueOf() function (and possibly toString()) in an attempt to convert
 * the object to a primitive value (possibly resulting in an uncaught script exception).
 *
 * See also `qmlbind_value_is_identical()`.
 *
 * libqmlbind's equivalent of [QJSValue::equals](https://doc.qt.io/qt-5/qjsvalue.html#equals).
 */
QMLBIND_API int qmlbind_value_is_equal(const qmlbind_value *value1, const qmlbind_value *value2);

/*!
 * \brief Returns true if `value1` is equal to `value2` using strict comparison (no conversion), otherwise returns false.
 *
 * The comparison follows the behavior described in
 * [ECMA-262](http://www.ecma-international.org/publications/standards/Ecma-262.htm) section 11.9.6, "The Strict
 * Equality Comparison Algorithm".
 *
 * If the type of `value1` is different from the type of the `value2`, this function returns false.
 * If the types are equal, the result depends on the type, as shown in the following table:
 *
 * | Type		| Result
 * | ---------- | ------------
 * | Undefined	| true
 * | Null		| true
 * | Boolean	| true if both values are true, false otherwise
 * | Number		| false if either value is NaN (Not-a-Number); true if values are equal, false otherwise
 * | String		| true if both values are exactly the same sequence of characters, false otherwise
 * | Object		|true if both values refer to the same object, false otherwise
 *
 * See also `qmlbind_value_is_equal()`.
 */
QMLBIND_API int qmlbind_value_is_identical(const qmlbind_value *value1, const qmlbind_value *value2);

/*!
 * \brief Returns true if this `qmlbind_value` is of the primitive type Undefined; otherwise returns false.
 *
 * libqmlbind's equivalent of [QJSValue::isUndefined](https://doc.qt.io/qt-5/qjsvalue.html#isUndefined).
 */
QMLBIND_API int qmlbind_value_is_undefined(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is of the primitive type Null; otherwise returns false.
 *
 * libqmlbind's equivalent of [QJSValue::isNull](https://doc.qt.io/qt-5/qjsvalue.html#isNull).
 */
QMLBIND_API int qmlbind_value_is_null(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is of the primitive type Boolean; otherwise returns false.
 *
 * libqmlbind's equivalent of [QJSValue::isBool](https://doc.qt.io/qt-5/qjsvalue.html#isBool).
 */
QMLBIND_API int qmlbind_value_is_boolean(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is of the primitive type Number; otherwise returns false.
 *
 * libqmlbind's equivalent of [QJSValue::isNumber](https://doc.qt.io/qt-5/qjsvalue.html#isNumber).
 */
QMLBIND_API int qmlbind_value_is_number(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is of the primitive type String; otherwise returns false.
 *
 * libqmlbind's equivalent of [QJSValue::isString](https://doc.qt.io/qt-5/qjsvalue.html#isString).
 */
QMLBIND_API int qmlbind_value_is_string(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is of the Object type; otherwise returns false.
 *
 * Note that function values and wrapper values are objects, so this function returns true for such
 * values.
 *
 * libqmlbind's equivalent of [QJSValue::isObject](https://doc.qt.io/qt-5/qjsvalue.html#isObject).
 */
QMLBIND_API int qmlbind_value_is_object(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is an object of the Array class; otherwise returns false.
 *
 * See also `qmlbind_engine_new_array()`.
 *
 * libqmlbind's equivalent of [QJSValue::isArray](https://doc.qt.io/qt-5/qjsvalue.html#isArray).
 */
QMLBIND_API int qmlbind_value_is_array(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` can be called as function, otherwise returns false.
 *
 * See also `qmlbind_value_call()`.
 *
 * libqmlbind's equivalent of [QJSValue::isCallable](https://doc.qt.io/qt-5/qjsvalue.html#isCallable).
 */
QMLBIND_API int qmlbind_value_is_function(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is an object of the Error class; otherwise returns false.
 *
 * libqmlbind's equivalent of [QJSValue::isError](https://doc.qt.io/qt-5/qjsvalue.html#isError).
 */
QMLBIND_API int qmlbind_value_is_error(const qmlbind_value *self);

/*!
 * \brief Returns true if this `qmlbind_value` is a wrapper around a C object; otherwise returns false.
 *
 * libqmlbind's rough equivalent of [QJSValue::isQObject](https://doc.qt.io/qt-5/qjsvalue.html#isQObject).
 */
QMLBIND_API int qmlbind_value_is_wrapper(const qmlbind_value *self);


/*!
 * \brief Constructs a new `qmlbind_value` with a boolean `value`.
 *
 * libqmlbind's equivalent of [QJSValue::QJSValue(bool)](https://doc.qt.io/qt-5/qjsvalue.html#QJSValue-3)
 */
QMLBIND_API qmlbind_value *qmlbind_value_new_boolean(int value);

/*!
 * \brief Returns the boolean value of this `qmlbind_value`, as defined in ECMA-262 section 9.2, "ToBoolean".
 *
 * Note that if this `qmlbind_value` is an object, calling this function has side effects on the script engine, since
 * the engine will call the object's valueOf() function (and possibly toString()) in an attempt to convert the object to
 * a primitive value (possibly resulting in an uncaught script exception).
 *
 * libqmlbind's equivalent of [QJSValue::toBool()](https://doc.qt.io/qt-5/qjsvalue.html#toBool).
 */
QMLBIND_API int qmlbind_value_get_boolean(const qmlbind_value *self);


/*!
 * \brief Constructs a new `qmlbind_value` with a number `value`.
 *
 * libqmlbind's equivalent of [QJSValue::QJSValue(double)](https://doc.qt.io/qt-5/qjsvalue.html#QJSValue-6)
 */
QMLBIND_API qmlbind_value *qmlbind_value_new_number(double value);

/*!
 * \brief Returns the number value of this `qmlbind_value`, as defined in ECMA-262 section 9.3, "ToNumber".
 *
 * Note that if this `qmlbind_value` is an object, calling this function has side effects on the script engine, since
 * the engine will call the object's valueOf() function (and possibly toString()) in an attempt to convert the object to
 * a primitive value (possibly resulting in an uncaught script exception).
 *
 * libqmlbind's equivalent of [QJSValue::toNumber()](https://doc.qt.io/qt-5/qjsvalue.html#toNumber).
 */
QMLBIND_API double qmlbind_value_get_number(const qmlbind_value *self);


/*!
 * \brief Constructs a new `qmlbind_value` with a the first `length` chars of string `value`.
 *
 * libqmlbind's equivalent of [QJSValue::QJSValue(const QString &)](https://doc.qt.io/qt-5/qjsvalue.html#QJSValue-7)
 */
QMLBIND_API qmlbind_value *qmlbind_value_new_string(int length, const char *value);

/*!
 * \brief Constructs a new `qmlbind_value` with a \0-terminated string `value`.
 *
 * libqmlbind's equivalent of [QJSValue::QJSValue(const QString &)](https://doc.qt.io/qt-5/qjsvalue.html#QJSValue-7)
 */
QMLBIND_API qmlbind_value *qmlbind_value_new_string_cstr(const char *value);

/*!
 * \brief Returns the string value of this `qmlbind_value`, as defined in ECMA-262 section 9.8, "ToString".
 * Ownership is transfered to the caller.
 *
 * Note that if this `qmlbind_value` is an object, calling this function has side effects on the script engine, since
 * the engine will call the object's valueOf() function (and possibly toString()) in an attempt to convert the object to
 * a primitive value (possibly resulting in an uncaught script exception).
 *
 * libqmlbind's equivalent of [QJSValue::toNumber()](https://doc.qt.io/qt-5/qjsvalue.html#toNumber).
 */
QMLBIND_API qmlbind_string *qmlbind_value_get_string(const qmlbind_value *self);


/*!
 * \brief Returns the value of this `qmlbind_value`'s property with the given `name`.
 * If no such property exists, an undefined `qmlbind_value` is returned.
 *
 * If the property is implemented using a getter function (i.e. has the PropertyGetter flag set), calling
 * `qmlbind_value_get_propert()` has side-effects on the script engine, since the getter function will be called
 * (possibly resulting in an uncaught script exception). If an exception occurred, property() returns the value that was
 * thrown (typically an Error object).
 *
 * Ownership of the returned `qmlbind_value` is transfered to the caller.
 *
 * libqmlbind's equivalent of [QJSValue::property()](https://doc.qt.io/qt-5/qjsvalue.html#property).
 */
QMLBIND_API qmlbind_value *qmlbind_value_get_property(const qmlbind_value *self, const char *key);

/*!
 * \brief Sets the value of this `qmlbind_value`'s property with the given `name` to the given `value`.
 *
 * If this `qmlbind_value` is not an object, this function does nothing.
 *
 * If this `qmlbind_value` does not already have a property with name `name`, a new property is created.
 *
 * libqmlbind's equivalent of [QJSValue::setProperty](https://doc.qt.io/qt-5/qjsvalue.html#setProperty).
 */
QMLBIND_API void qmlbind_value_set_property(qmlbind_value *self, const char *key, const qmlbind_value *value);

/*!
 * \brief Attempts to delete this object's property of the given `name`.
 * Returns true if the property was deleted, otherwise returns false.
 *
 * The behavior of this function is consistent with the JavaScript delete operator. In particular:
 *
 * - Non-configurable properties cannot be deleted.
 * - This function will return true even if this object doesn't have a property of the given name (i.e., non-existent
 *   properties are "trivially deletable").
 * - If this object doesn't have an own property of the given name, but an object in the prototype() chain does, the
 *   prototype object's property is not deleted, and this function returns true.
 *
 * See also `qmlbind_value_set_property()` and `qmlbind_value_has_own_property()`.
 *
 * libqmlbind's equivalent of [QJSValue::deleteProperty()](https://doc.qt.io/qt-5/qjsvalue.html#deleteProperty).
 */
QMLBIND_API int qmlbind_value_delete_property(qmlbind_value *self, const char *key);

/*!
 * \brief Returns true if this object has a property of the given name, otherwise returns false.
 *
 * See also `qmlbind_value_get_property()` and `qmlbind_value_has_own_property()`.
 *
 * libqmlbind's equivalent of [QJSValue::hasProperty()](https://doc.qt.io/qt-5/qjsvalue.html#hasProperty).
 */
QMLBIND_API int qmlbind_value_has_property(const qmlbind_value *self, const char *key);


/*!
 * \brief Returns true if this object has an own (not prototype-inherited) property of the given name,
 * otherwise returns false.
 *
 * See also `qmlbind_value_get_property()` and `qmlbind_value_has_property()`.
 *
 * libqmlbind's equivalent of [QJSValue::hasOwnProperty](https://doc.qt.io/qt-5/qjsvalue.html#hasOwnProperty).
 */
QMLBIND_API int qmlbind_value_has_own_property(const qmlbind_value *self, const char *key);

/*!
 * \brief If this `qmlbind_value` is an object, returns the internal prototype (__proto__ property) of this object;
 * otherwise returns an undefined `qmlbind_value`.
 *
 * See also `qmlbind_value_set_prototype()` and `qmlbind_value_is_object()`.
 *
 * libqmlbind's equivalent of [QJSValue::prototype()](https://doc.qt.io/qt-5/qjsvalue.html#prototype).
 */
QMLBIND_API qmlbind_value *qmlbind_value_get_prototype(const qmlbind_value *self);

/*!
 * \brief If this `qmlbind_value` is an object, sets the internal prototype (__proto__ property) of this object to be
 * prototype; if the `qmlbind_value` is null, it sets the prototype to null; otherwise does nothing.
 *
 * The internal prototype should not be confused with the public property with name "prototype"; the public prototype is
 * usually only set on functions that act as constructors.
 *
 * See also `qmlbind_value_get_prototype()` and `qmlbind_value_is_object()`.

 * libqmlbind's equivalent of [QJSValue::setPrototype()](https://doc.qt.io/qt-5/qjsvalue.html#setPrototype).
 */
QMLBIND_API void qmlbind_value_set_prototype(qmlbind_value *self, const qmlbind_value *proto);


/*!
 * \brief Returns true if this object has a property `index`, otherwise returns false.
 *
 * This function is provided for convenience when working with array objects.
 *
 * If this `qmlbind_value` is not an Array object, this function behaves as if `qmlbind_value_get_property()` was called
 * with the string representation of `index`.
 */
QMLBIND_API int qmlbind_value_has_index(const qmlbind_value *self, int index);

/*!
 * \brief Returns the property at the given `index`.
 *
 * This function is provided for convenience and performance when working with array objects.
 *
 * If this `qmlbind_value` is not an Array object, this function behaves as if `qmlbind_value_get_property()` was called
 * with the string representation of `index`.
 *
 * libqmlbind's equivalent of [QJSValue::property(quint32 arrayIndex)](https://doc.qt.io/qt-5/qjsvalue.html#property-1).
 */
QMLBIND_API qmlbind_value *qmlbind_value_get_array_item(const qmlbind_value *self, int index);


/*!
 * \brief Sets the property at the given `index` to the given value.
 *
 * This function is provided for convenience and performance when working with array objects.
 *
 * If this `qmlbind_value` is not an Array object, this function behaves as if `qmlbind_value_set_property()` was called
 * with the string representation of `index`.
 *
 * libqmlbind's equivalent of
 * [QJSValue::setProperty(quint32 arrayIndex, const QJSValue&](https://doc.qt.io/qt-5/qjsvalue.html#setProperty-1).
 */
QMLBIND_API void qmlbind_value_set_array_item(qmlbind_value *self, int index, const qmlbind_value *property);



/*!
 * \brief Calls this `qmlbind_value` as a function, passing `argc` number of arguments from `argv` as arguments to the
 * function, and using the globalObject() as the "this"-object. Returns the value returned from the function.
 *
 * Ownership of the returned value is transfered to the caller.
 *
 * If this `qmlbind_value` is not callable, `qmlbind_value_call()` does nothing and returns an undefined `qmlbind_value`.
 *
 * Calling `qmlbind_value_call()` can cause an exception to occur in the script engine; in that case,
 * `qmlbind_value_call()` returns the value that was thrown (typically an Error object). You can call
 * `qmlbind_value_is_error()` on the return value to determine whether an exception occurred.
 *
 * See also `qmlbind_value_is_function()`, `qmlbind_value_call_with_instance()`, and
 * `qmlbind_value_call_as_constructor().
 *
 * libqmlbind's equivalent of [QJSValue::call()](https://doc.qt.io/qt-5/qjsvalue.html#call).
 */
QMLBIND_API qmlbind_value *qmlbind_value_call(
    qmlbind_value *self,
    int argc,
    const qmlbind_value *const *argv
);

/*!
 * \brief Creates a new Object and calls this `libqmlbind_value` as a constructor, using the created object as the
 * `this' object and passing `argc` number of arguments from `argv` as arguments.
 *
 * If the return value from the constructor call is an object, then that object is returned; otherwise the default
 * constructed object is returned.
 *
 * Ownership of the returned value is transfered to the caller.
 *
 * If this `qmlbind_value` is not a function, `qmlbind_value_call_constructor()` does nothing and returns an undefined
 * `qmlbind_value`.
 *
 * Calling this function can cause an exception to occur in the script engine; in that case, the value that was thrown
 * (typically an Error object) is returned. You can call `qmlbind_value_is_error()` on the return value to determine
 * whether an exception occurred.
 *
 * See also `qmlbind_value_call()` and `qmlbind_engine_new_object()`.
 *
 * libqmlbind's equivalent of [QJSValue::callAsConstructor()](https://doc.qt.io/qt-5/qjsvalue.html#callAsConstructor).
 */
QMLBIND_API qmlbind_value *qmlbind_value_call_constructor(
    qmlbind_value *function,
    int argc,
    const qmlbind_value *const *argv
);

/*!
 * \brief Calls this `qmlbind_value` as a function, using instance as the `this' object in the function call, and
 * passing `argc` number of arguments from `argv` as arguments to the function. Returns the value returned from the
 * function.
 *
 * If this `qmlbind_value` is not a function, this does nothing and returns an undefined `qmlbind_value`.
 *
 * Ownership of the returned value is transfered to the caller.
 *
 * Note that if instance is not an object, the global object (see `qmlbind_engine_get_global_object()`) will be used as
 * the `this' object.
 *
 * Calling this function can cause an exception to occur in the script engine; in that case, the value that was thrown
 * (typically an Error object) is returned. You can call `qmlbind_value_is_error()` on the return value to determine
 * whether an exception occurred.
 *
 *
 * See also `qmlbind_value_call()`.
 *
 * libqmlbind's equivalent of [QJSValue::callWithInstance()](https://doc.qt.io/qt-5/qjsvalue.html#callWithInstance).
 */
QMLBIND_API qmlbind_value *qmlbind_value_call_with_instance(
    qmlbind_value *self,
    qmlbind_value *instance,
    int argc,
    const qmlbind_value *const *argv
);

/*!
 * \brief If this `qmlbind_value` is a wrapper, returns the `qmlbind_client_object` inside the wrapper; otherwise, returns 0.
 *
 * Does not transfer ownership of the unwrapped `qmlbind_client_object`.
 *
 * libqmlbind's rough equivalent of [QJSValue::toQObject()](https://doc.qt.io/qt-5/qjsvalue.html#toQObject).
 */
QMLBIND_API qmlbind_client_object *qmlbind_value_unwrap(const qmlbind_value *self);

#ifdef __cplusplus
}
#endif
