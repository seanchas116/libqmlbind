#pragma once

#include <QTimer>

class TickTimer : public QTimer
{
    Q_OBJECT
public:
    typedef void (*Callback)();

    explicit TickTimer(QObject *parent = 0);
    void setCallback(Callback cb);

private slots:
    void onTimeout();

private:
    Callback mCallback = nullptr;
};

