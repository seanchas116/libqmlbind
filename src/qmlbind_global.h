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

typedef struct QApplication qmlbind_application;

typedef struct QQmlEngine qmlbind_engine;
typedef struct QQmlContext qmlbind_context;

typedef struct QJSValue qmlbind_value;
typedef struct QJSValueIterator qmlbind_iterator;
typedef struct QByteArray qmlbind_string;

typedef struct qmlbind_object_s qmlbind_object;
typedef struct qmlbind_class_s qmlbind_class;
