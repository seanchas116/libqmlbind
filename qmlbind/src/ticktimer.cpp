#include "ticktimer.h"

TickTimer::TickTimer(Callback *whereCallback, QObject *parent) : QTimer(parent), mWhereCallback(whereCallback)
{
    setInterval(0);
    setSingleShot(false);
    connect(this, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void TickTimer::onTimeout()
{
    if (*mWhereCallback) {
        (*mWhereCallback)();
    }
}
