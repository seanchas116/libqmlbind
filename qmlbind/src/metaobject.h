#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QScopedPointer>
#include <QSharedPointer>
#include <private/qobject_p.h>

namespace QmlBind {

class Exporter;
class Wrapper;
class Backref;
class SignalEmitter;

class MetaObject : public QMetaObject, public QEnableSharedFromThis<MetaObject>
{
public:
    MetaObject(const std::shared_ptr<const Exporter> &exporter);
    ~MetaObject();

    Wrapper *newWrapper(qmlbind_client_object *object) const;
    Backref newObject(SignalEmitter *emitter) const;

    int metaCall(QObject *object, Call call, int index, void **argv) const;

private:

    std::shared_ptr<const Exporter> mExporter;
    std::shared_ptr<QMetaObject> mPrototype;
};

} // namespace QmlBind
