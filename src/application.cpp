#include "application.h"
#include <QApplication>

extern "C" {

qmlbind_application *qmlbind_application_new(int argc, char **argv) {
    return new QApplication(argc, argv);
}

void qmlbind_application_delete(qmlbind_application *app) {
    delete app;
}

void qmlbind_application_process_events(qmlbind_application *app) {
    Q_UNUSED(app);
    QCoreApplication::processEvents();
    QCoreApplication::sendPostedEvents(0, QEvent::DeferredDelete);
}

}
