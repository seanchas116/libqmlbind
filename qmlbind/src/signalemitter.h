#pragma once

#include <QPointer>
#include "wrapper.h"

class QByteArray;

namespace QmlBind {

class Wrapper;

class SignalEmitter
{
public:
    SignalEmitter();

    void setWrapper(Wrapper *wrapper) { mWrapper = wrapper; }
    void emitSignal(const QByteArray &name, int argc, QJSValue **argv);

private:
    QPointer<Wrapper> mWrapper;
};

} // namespace QmlBind
