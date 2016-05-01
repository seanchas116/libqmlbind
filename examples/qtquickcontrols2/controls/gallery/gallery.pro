TEMPLATE = app
CONFIG -= app_bundle
QMAKE_CFLAGS += "-std=c99"
QT += quick

SOURCES += \
    gallery.c

OTHER_FILES += \
    gallery.qml

RESOURCES += \
    gallery.qrc

QMAKE_RPATHDIR += $$OUT_PWD/../../../../qmlbind
LIBS += -L$$OUT_PWD/../../../../qmlbind/ -lqmlbind
INCLUDEPATH += $$PWD/../../../../qmlbind/include
DEPENDPATH += $$PWD/../../../../qmlbind
