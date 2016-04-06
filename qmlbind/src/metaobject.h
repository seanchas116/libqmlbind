#pragma once

#include "qmlbind/qmlbind_global.h"
#include <private/qobject_p.h>

namespace QmlBind {

class Exporter;
class Wrapper;
class SignalEmitter;

class MetaObject : public QMetaObject, public std::enable_shared_from_this<MetaObject>
{
public:
    MetaObject(std::unique_ptr<const Exporter> &&exporter, QMetaObject* prototype);
    MetaObject(std::unique_ptr<const Exporter> &&exporter, std::unique_ptr<QMetaObject, decltype(&free)> prototype);

    Wrapper *newWrapper(qmlbind_client_object *object) const;
    Wrapper *newObject(void *memory) const;

    // needed because indexOfSignal() needs the full normalized signal signature, not only the name.
    int indexOfSignalName(const char *name) const;

    int metaCall(QObject *object, Call call, int index, void **argv) const;

private:

    std::unique_ptr<const Exporter> mExporter;
    std::unique_ptr<QMetaObject, decltype(&free)> mPrototype;
};

} // namespace QmlBind
