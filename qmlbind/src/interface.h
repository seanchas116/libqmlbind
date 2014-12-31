#pragma once

#include "qmlbind/qmlbind_global.h"
#include <private/qmetaobjectbuilder_p.h>

namespace QmlBind {

class Interface
{
public:

    struct Method {
        void *handle;
        int arity;
    };

    struct Property {
        void *setterHandle;
        void *getterHandle;
    };

    Interface(const char *className, void *classHandle, qmlbind_interface_handlers handlers);

    QMetaMethodBuilder addMethod(void *handle, const char *name, int arity);
    QMetaMethodBuilder addSignal(const char *name, int arity);
    QMetaPropertyBuilder addProperty(void *getterHandle, void *setterHandle,
                                     const char *name, int notifySignalIndex);

    void *classHandle() const;
    const QMetaObjectBuilder *metaObjectBuilder() const;
    qmlbind_interface_handlers handlers() const;
    QHash<int, Method> methodMap() const;
    QHash<int, Property> propertyMap() const;

private:

    void *mClassHandle;
    qmlbind_interface_handlers mHandlers;
    QHash<int, Method> mMethodMap;
    QHash<int, Property> mPropertyMap;

    QMetaObjectBuilder mBuilder;
};

} // namespace QmlBind
