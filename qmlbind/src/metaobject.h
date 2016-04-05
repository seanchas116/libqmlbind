#pragma once

#include "qmlbind/qmlbind_global.h"
#include "exporter.h"
#include <QScopedPointer>
#include <QSharedPointer>
#include <private/qobject_p.h>

namespace QmlBind {

class Exporter;
class Wrapper;

class MetaObject : public QMetaObject
{
public:
    MetaObject(const std::shared_ptr<const Exporter> &exporter);
    ~MetaObject();

    std::shared_ptr<const Exporter> exporter() const { return mExporter; }
    int metaCall(QObject *object, Call call, int index, void **argv) const;

private:

    std::shared_ptr<const Exporter> mExporter;
    std::shared_ptr<QMetaObject> mPrototype;
};

} // namespace QmlBind
