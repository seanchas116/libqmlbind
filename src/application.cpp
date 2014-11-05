#include "application.h"
#include <QApplication>

extern "C" {

typedef struct qmlbind_application_s {
    QApplication *d;
} qmlbind_application;

qmlbind_application *qmlbind_application_new(int argc, char **argv) {
    qmlbind_application *app = new qmlbind_application();
    app->d = new QApplication(argc, argv);
    return app;
}

void qmlbind_application_delete(qmlbind_application *app) {
    delete app->d;
    delete app;
}

void qmlbind_application_process_events(qmlbind_application *app) {
    Q_UNUSED(app);
    QCoreApplication::processEvents();
    QCoreApplication::sendPostedEvents(0, QEvent::DeferredDelete);
}

}
