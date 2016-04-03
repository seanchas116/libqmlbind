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
    const Wrapper *wrapper() const { return mWrapper; }
    void emitSignal(const QByteArray &name, int argc, const QJSValue *const *argv) const;

private:
    QPointer<Wrapper> mWrapper;
};

} // namespace QmlBind
