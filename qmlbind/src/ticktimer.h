#pragma once

#include <QTimer>

class TickTimer : public QTimer
{
    Q_OBJECT
public:
    typedef QAtomicPointer<void ()> Callback;

    explicit TickTimer(Callback *callback, QObject *parent = 0);

private slots:
    void onTimeout();

private:
    Callback *mCallback;
};

