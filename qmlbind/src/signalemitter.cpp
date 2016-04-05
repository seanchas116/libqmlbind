#include "signalemitter.h"
#include "metaobject.h"
#include "exporter.h"
#include <QDebug>

namespace QmlBind {

SignalEmitter::SignalEmitter()
{
}

void SignalEmitter::emitSignal(const QByteArray &name, int argc, const QJSValue *const *argv) const
{
    std::shared_ptr<const MetaObject> metaObj = mWrapper->qmlbindMetaObject();
    int index = metaObj->exporter()->signalIndexMap().value(name, -1);
    if (index == -1) {
        qWarning() << "no such signal found:" << name;
        return;
    }
    int offset = metaObj->methodOffset();

    QMetaMethod signal = metaObj->method(index + offset);
    if (signal.parameterCount() != argc) {
        qWarning() << "parameter count wrong:" << name;
        return;
    }
    Q_ASSERT(signal.name() == name);

    // If the signal is connected to any slot / method with a return value,
    // it is written to the front element of the argv array.
    // This is undocumented behaviour, and therefore we don't forward that return value through libqmlbind.
    // Source: http://stackoverflow.com/questions/5842124/can-qt-signals-return-a-value/5903082
    // Still, we need to allocate a new array with nullptr as front element and the argv values behind that.
    const QJSValue *argv_with_retvalue[argc + 1];
    argv_with_retvalue[0] = nullptr;
    std::copy(argv, argv + argc, argv_with_retvalue + 1);

    QMetaObject::activate(mWrapper, metaObj.get(), index,
                          const_cast<void**>(reinterpret_cast<const void **>(argv_with_retvalue)));
}

} // namespace QmlBind

