QT += widgets qml quick core-private

TARGET = qmlbind
TEMPLATE = lib

DEFINES += QMLBIND_LIBRARY

INCLUDEPATH += $$PWD/headers

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += "-std=c++03"

SOURCES += \
    src/api_application.cpp \
    src/api_engine.cpp \
    src/api_iterator.cpp \
    src/api_value.cpp \
    src/metaobject.cpp \
    src/object.cpp \
    src/interface.cpp \
    src/api_metaobject.cpp \
    src/api_interface.cpp

HEADERS += \
    headers/qmlbind/application.h \
    headers/qmlbind/engine.h \
    headers/qmlbind/iterator.h \
    headers/qmlbind/qmlbind_global.h \
    headers/qmlbind/value.h \
    src/metaobject.h \
    src/object.h \
    src/interface.h \
    headers/qmlbind/interface.h \
    headers/qmlbind/metaobject.h
