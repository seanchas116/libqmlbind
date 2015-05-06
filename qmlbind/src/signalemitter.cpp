#include "signalemitter.h"
#include "metaobject.h"
#include "exporter.h"
#include <QDebug>

namespace QmlBind {

SignalEmitter::SignalEmitter()
{
}

void SignalEmitter::emitSignal(const QByteArray &name, int argc, QJSValue **argv)
{
    QSharedPointer<const MetaObject> metaObj = mWrapper->qmlbindMetaObject();
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

    QMetaObject::activate(mWrapper, metaObj.data(), index, reinterpret_cast<void **>(argv - 1));
}

} // namespace QmlBind

