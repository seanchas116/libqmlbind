#include "qmlbind/application.h"
#include "util.h"
#include "ticktimer.h"
#include "backref.h"
#include <QApplication>
#include <QSharedPointer>
#include <QTimer>
#include <QVector>

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

class AppArgs
{
public:
    AppArgs(int argc, char **argv) :
        mArgs(argc), mArgc(argc), mArgv(argc)
    {
        for (int i = 0; i < argc; ++i) {
            mArgs[i] = argv[i];
        }
        for (int i = 0; i < argc; ++i) {
            mArgv[i] = mArgs[i].data();
        }
    }

    int &argc()
    {
        return mArgc;
    }

    char **argv()
    {
        return mArgv.data();
    }

private:
    QVector<QByteArray> mArgs;
    int mArgc;
    QVector<char *> mArgv;
};

}

static void (*tickCallback)();

extern "C" {

qmlbind_application qmlbind_application_new(int argc, char **argv)
{
    AppArgs *args = new AppArgs(argc, argv);
    QApplication *app = new QApplication(args->argc(), args->argv());

    TickTimer *timer = new TickTimer(&tickCallback, app);
    timer->start();

    return app;
}

void qmlbind_application_release(qmlbind_application app)
{
    delete app;
}

int qmlbind_application_exec(qmlbind_application app)
{
    return app->exec();
}

void qmlbind_process_events()
{
    QCoreApplication::processEvents();
    QCoreApplication::sendPostedEvents(0, QEvent::DeferredDelete);
}

void qmlbind_set_tick_callback(void (*func)())
{
    tickCallback = func;
}

void qmlbind_next_tick(qmlbind_interface interface, void (*func)(qmlbind_backref), qmlbind_backref data)
{
    QTimer::singleShot(0, NextTickFunc(func, Backref(data, *interface)));
}

}
