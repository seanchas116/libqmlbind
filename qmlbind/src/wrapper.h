#pragma once

#include "qmlbind/qmlbind_global.h"
#include <QObject>

namespace QmlBind {

class MetaObject;

class Wrapper : public QObject
{
public:
    Wrapper(const MetaObject *metaObject, void *handle);
    ~Wrapper();

    const QMetaObject *metaObject() const Q_DECL_OVERRIDE;
    int qt_metacall(QMetaObject::Call call, int index, void **argv) Q_DECL_OVERRIDE;

    void *handle() const;

private:

    const MetaObject *mMetaObject;
    void *mHandle;
};

} // namespace QmlBind
