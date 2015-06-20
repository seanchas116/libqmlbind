#include "ticktimer.h"
#include <QCoreApplication>

TickTimer::TickTimer(QObject *parent) : QTimer(parent)
{
    setInterval(0);
    setSingleShot(false);
    connect(this, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void TickTimer::setCallback(Callback cb) {
    QTimer::singleShot(0, this, [&] {
        if (cb) {
            mCallback = cb;
            start();
        } else {
            stop();
        }
    });
    QCoreApplication::processEvents();
}

void TickTimer::onTimeout()
{
    if (mCallback) {
        mCallback();
    }
}
