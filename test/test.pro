TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

SOURCES += \
    api.c \
    main.cpp \
    test_value.cpp \
    test_engine.cpp \
    test_interface.cpp

QMAKE_CFLAGS += "-std=c89"

LIBS += -L$$PWD/../qmlbind/ -lqmlbind
INCLUDEPATH += $$PWD/../qmlbind/headers $$PWD/lib/Catch/include
DEPENDPATH += $$PWD/../qmlbind

HEADERS += \
    test_helper.h
