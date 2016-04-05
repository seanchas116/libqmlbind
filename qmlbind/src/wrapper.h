#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QObject>
#include <QSharedPointer>
#include "interface.h"

namespace QmlBind {

class MetaObject;

class Wrapper : public QObject
{
public:
    Wrapper(const std::shared_ptr<const MetaObject> &metaObject, Interface&& interface);

    const QMetaObject *metaObject() const Q_DECL_OVERRIDE;
    int qt_metacall(QMetaObject::Call call, int index, void **argv) Q_DECL_OVERRIDE;

    const Interface &interface() { return mInterface; }
    const std::shared_ptr<const MetaObject> qmlbindMetaObject() const { return mMetaObject; }

private:

    std::shared_ptr<const MetaObject> mMetaObject;
    Interface mInterface;
};

} // namespace QmlBind
