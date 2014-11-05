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

typedef struct qmlbind_application_s qmlbind_application;

typedef struct qmlbind_engine_s qmlbind_engine;
typedef struct qmlbind_context_s qmlbind_context;

typedef struct qmlbind_value_s qmlbind_value;
typedef struct qmlbind_iterator_s qmlbind_iterator;
typedef struct qmlbind_string_s qmlbind_string;

typedef struct qmlbind_object_s qmlbind_object;
typedef struct qmlbind_class_s qmlbind_class;
