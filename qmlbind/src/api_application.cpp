#include "qmlbind/application.h"
#include "util.h"
#include "backref.h"
#include <QApplication>
#include <QSharedPointer>
#include <QTimer>

using namespace QmlBind;

namespace QmlBind {

class NextTickFunc
{
public:
    NextTickFunc(void (*func)(qmlbind_backref), const Backref &data) : mFunc(func), mData(data)
    {}

    void operator()()
    {
        mFunc(mData.backref());
    }

private:
    void (*mFunc)(qmlbind_backref);
    Backref mData;
};

}

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

void qmlbind_next_tick(qmlbind_interface interface, void (*func)(qmlbind_backref), qmlbind_backref data)
{
    QTimer::singleShot(0, NextTickFunc(func, Backref(data, *interface)));
}

}
