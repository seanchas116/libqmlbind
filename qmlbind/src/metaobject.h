#pragma once

#include "qmlbind/qmlbind_global.h"
#include "interface.h"
#include <QScopedPointer>
#include <QSharedPointer>
#include <private/qobject_p.h>

namespace QmlBind {

class Interface;
class Wrapper;

class MetaObject : public QMetaObject
{
public:
    MetaObject(const QSharedPointer<const Interface> &interface);
    ~MetaObject();

    QSharedPointer<const Interface> interface() const { return mInterface; }
    int metaCall(QObject *object, Call call, int index, void **argv) const;

private:

    QSharedPointer<const Interface> mInterface;
    qmlbind_interface_handlers mHandlers;
    QHash<int, Interface::Method> mMethods;
    QHash<int, Interface::Property> mProperties;
    QScopedPointer<QMetaObject, QScopedPointerPodDeleter> mPrototype;
};

} // namespace QmlBind
