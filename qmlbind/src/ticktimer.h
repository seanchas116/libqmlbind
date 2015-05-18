#pragma once

#include <QTimer>

class TickTimer : public QTimer
{
    Q_OBJECT
public:
    typedef void (*Callback)();

    explicit TickTimer(Callback *whereCallback, QObject *parent = 0);

private slots:
    void onTimeout();

private:
    Callback *mWhereCallback;
};

