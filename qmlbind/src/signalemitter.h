#pragma once

#include <QPointer>
#include "wrapper.h"

class QByteArray;

namespace QmlBind {

class Wrapper;

class SignalEmitter
{
public:
    SignalEmitter(Wrapper *wrapper);

    Engine *getEngine() const;
    void emitSignal(const QByteArray &name, int argc, const QJSValue *const *argv) const;

private:
    QPointer<Wrapper> mWrapper;
};

} // namespace QmlBind
