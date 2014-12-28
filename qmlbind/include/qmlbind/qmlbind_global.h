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

#ifdef QMLBIND_LIBRARY

namespace QmlBind {

class MetaObject;
class Interface;

}

template <typename T> class QList;

typedef class QApplication qmlbind_application;

typedef class QQmlEngine qmlbind_engine;
typedef class QQmlContext qmlbind_context;
typedef class QQmlComponent qmlbind_component;

typedef class QJSValue qmlbind_value;
typedef class QJSValueIterator qmlbind_iterator;
typedef class QByteArray qmlbind_string;
typedef class QList<QByteArray> qmlbind_string_list;

typedef QmlBind::MetaObject qmlbind_metaobject;
typedef QmlBind::Interface qmlbind_interface;

#else

typedef struct qmlbind_application_s qmlbind_application;

typedef struct qmlbind_engine_s qmlbind_engine;
typedef struct qmlbind_context_s qmlbind_context;
typedef struct qmlbind_component_s qmlbind_component;

typedef struct qmlbind_value_s qmlbind_value;
typedef struct qmlbind_iterator_s qmlbind_iterator;
typedef struct qmlbind_string_s qmlbind_string;
typedef struct qmlbind_string_list_s qmlbind_string_list;

typedef struct qmlbind_object_s qmlbind_object;
typedef struct qmlbind_metaobject_s qmlbind_metaobject;
typedef struct qmlbind_interface_s qmlbind_interface;

#endif

typedef struct {
    qmlbind_value *(*call_method)(void *objHandle, void *methodHandle, int argc, qmlbind_value **argv);
    qmlbind_value *(*get_property)(void *objHandle, void *getterHandle);
    void (*set_property)(void *objHandle, void *setterHandle, qmlbind_value *value);
} qmlbind_interface_handlers;
