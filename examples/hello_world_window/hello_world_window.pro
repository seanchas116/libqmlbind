TEMPLATE = app
CONFIG -= app_bundle
CONFIG += c++11
QMAKE_CFLAGS += "-std=c99"

SOURCES += main.c


QMAKE_RPATHDIR += $$OUT_PWD/../../qmlbind
LIBS += -L$$OUT_PWD/../../qmlbind/ -lqmlbind
INCLUDEPATH += $$PWD/../../qmlbind/include $$PWD/lib/Catch/include
DEPENDPATH += $$PWD/../../qmlbind
