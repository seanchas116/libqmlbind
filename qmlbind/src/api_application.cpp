#include "qmlbind/application.h"
#include "util.h"
#include "backref.h"
#include <QApplication>
#include <QSharedPointer>
#include <QTimer>
#include <QVector>

using namespace QmlBind;

namespace QmlBind {

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

extern "C" {

qmlbind_application qmlbind_application_new(int argc, char **argv)
{
    AppArgs *args = new AppArgs(argc, argv);
    QApplication *app = new QApplication(args->argc(), args->argv());

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

void qmlbind_next_tick(void (*callback)(void *), void *data)
{
    QTimer::singleShot(0, [=] {
        callback(data);
    });
}

}
