TEMPLATE = app
QT += qml
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
QMAKE_CFLAGS += "-std=c99"

SOURCES += \
    api.c \
    main.cpp \
    engine_test.cpp \
    value_test.cpp \
    iterator_test.cpp \
    component_test.cpp \
    exporter_test.cpp \
    application_test.cpp \
    fixtures/emptycallbacks.cpp \
    plugin_test.cpp


QMAKE_RPATHDIR += $$OUT_PWD/../qmlbind
LIBS += -L$$OUT_PWD/../qmlbind/ -lqmlbind
INCLUDEPATH += $$PWD/../qmlbind/include $$PWD/lib/Catch/include
DEPENDPATH += $$PWD/../qmlbind

HEADERS += \
    test_helper.h \
    fixtures/emptycallbacks.h
