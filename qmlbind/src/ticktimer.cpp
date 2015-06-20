#include "ticktimer.h"

TickTimer::TickTimer(Callback *callback, QObject *parent) : QTimer(parent), mCallback(callback)
{
    setInterval(0);
    setSingleShot(false);
    connect(this, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void TickTimer::onTimeout()
{
    void (*callback)() = mCallback->load();
    if (callback) {
        callback();
    }
}
