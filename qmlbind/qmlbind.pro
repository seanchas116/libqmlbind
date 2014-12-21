QT += widgets qml quick core-private

TARGET = qmlbind
TEMPLATE = lib

DEFINES += QMLBIND_LIBRARY

INCLUDEPATH += $$PWD/include

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
    src/interface.cpp \
    src/api_metaobject.cpp \
    src/api_interface.cpp \
    src/wrapper.cpp

HEADERS += \
    include/qmlbind/application.h \
    include/qmlbind/engine.h \
    include/qmlbind/iterator.h \
    include/qmlbind/qmlbind_global.h \
    include/qmlbind/value.h \
    src/metaobject.h \
    src/interface.h \
    include/qmlbind/interface.h \
    include/qmlbind/metaobject.h \
    src/wrapper.h
