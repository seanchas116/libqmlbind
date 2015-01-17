#include "qmlbind/application.h"
#include "util.h"
#include <QApplication>
#include <QSharedPointer>

using namespace QmlBind;

extern "C" {

qmlbind_application qmlbind_application_new(int argc, char **argv)
{
    return new QApplication(argc, argv);
}

void qmlbind_application_release(qmlbind_application app)
{
    delete app;
}

void qmlbind_process_events()
{
    QCoreApplication::processEvents();
    QCoreApplication::sendPostedEvents(0, QEvent::DeferredDelete);
}

}
