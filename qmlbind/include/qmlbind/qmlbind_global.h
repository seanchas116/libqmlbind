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

typedef class QApplication *qmlbind_application;

typedef class QQmlEngine *qmlbind_engine;
typedef class QQmlComponent *qmlbind_component;

typedef class QJSValue *qmlbind_value;
typedef class QJSValueIterator *qmlbind_iterator;
typedef class QByteArray *qmlbind_string;

typedef QmlBind::MetaObject *qmlbind_metaobject;
typedef QmlBind::Interface *qmlbind_interface;

#else

typedef struct qmlbind_application_s *qmlbind_application;

typedef struct qmlbind_engine_s *qmlbind_engine;
typedef struct qmlbind_component_s *qmlbind_component;

typedef struct qmlbind_value_s *qmlbind_value;
typedef struct qmlbind_iterator_s *qmlbind_iterator;
typedef struct qmlbind_string_s *qmlbind_string;

typedef struct qmlbind_metaobject_s *qmlbind_metaobject;
typedef struct qmlbind_interface_s *qmlbind_interface;

#endif

typedef struct {} *qmlbind_class_handle;
typedef struct {} *qmlbind_object_handle;
typedef struct {} *qmlbind_method_handle;
typedef struct {} *qmlbind_setter_handle;
typedef struct {} *qmlbind_getter_handle;

typedef struct {
    qmlbind_object_handle (*new_object)(qmlbind_class_handle classHandle);
    void (*delete_object)(qmlbind_object_handle objHandle);
    qmlbind_value (*call_method)(qmlbind_object_handle objHandle, qmlbind_method_handle methodHandle, int argc, qmlbind_value *argv);
    qmlbind_value (*get_property)(qmlbind_object_handle objHandle, qmlbind_getter_handle getterHandle);
    void (*set_property)(qmlbind_object_handle objHandle, qmlbind_setter_handle setterHandle, qmlbind_value value);
} qmlbind_interface_handlers;
