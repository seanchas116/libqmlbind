#pragma once

#include "qmlbind/qmlbind_global.h"
#include "interface.h"
#include <QScopedPointer>
#include <private/qobject_p.h>

namespace QmlBind {

class Interface;

class MetaObject : public QMetaObject
{
public:
    MetaObject(Interface *interface);
    ~MetaObject();

    int metaCall(QObject *object, Call call, int index, void **argv) const;

private:

    QScopedPointer<Interface> mInterface;
    qmlbind_interface_handlers mHandlers;
    QHash<int, Interface::Method> mMethods;
    QHash<int, Interface::Property> mProperties;
    QMetaObject *mPrototype;
};

} // namespace QmlBind
