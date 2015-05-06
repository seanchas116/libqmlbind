QT += widgets qml quick core-private

TARGET = qmlbind
TEMPLATE = lib

DEFINES += QMLBIND_LIBRARY

INCLUDEPATH += $$PWD/include

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/api_application.cpp \
    src/api_engine.cpp \
    src/api_iterator.cpp \
    src/api_value.cpp \
    src/metaobject.cpp \
    src/api_metaobject.cpp \
    src/wrapper.cpp \
    src/api_string.cpp \
    src/api_component.cpp \
    src/typeregisterer.cpp \
    src/api_register.cpp \
    src/exporter.cpp \
    src/api_exporter.cpp \
    src/api_interface.cpp \
    src/interface.cpp \
    src/backref.cpp \
    src/signalemitter.cpp \
    src/api_signal_emitter.cpp

HEADERS += \
    include/qmlbind/application.h \
    include/qmlbind/engine.h \
    include/qmlbind/iterator.h \
    include/qmlbind/qmlbind_global.h \
    include/qmlbind/value.h \
    src/metaobject.h \
    include/qmlbind/metaobject.h \
    src/wrapper.h \
    include/qmlbind/string.h \
    include/qmlbind/component.h \
    include/qmlbind.h \
    src/typeregisterer.h \
    include/qmlbind/register.h \
    src/util.h \
    src/exporter.h \
    include/qmlbind/exporter.h \
    include/qmlbind/interface.h \
    src/interface.h \
    src/backref.h \
    src/signalemitter.h \
    include/qmlbind/signal_emitter.h
