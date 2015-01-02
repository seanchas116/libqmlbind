#pragma once

#include "qmlbind/qmlbind_global.h"
#include <private/qmetaobjectbuilder_p.h>

namespace QmlBind {

class Interface
{
public:

    struct Method {
        qmlbind_method_handle handle;
        int arity;
    };

    struct Property {
        qmlbind_setter_handle setterHandle;
        qmlbind_getter_handle getterHandle;
    };

    Interface(const char *className, qmlbind_class_handle classHandle, qmlbind_interface_handlers handlers);

    QMetaMethodBuilder addMethod(qmlbind_method_handle handle, const char *name, int arity);
    QMetaMethodBuilder addSignal(const char *name, int arity);
    QMetaPropertyBuilder addProperty(qmlbind_getter_handle getterHandle, qmlbind_setter_handle setterHandle,
                                     const char *name, int notifySignalIndex);

    qmlbind_class_handle classHandle() const;
    const QMetaObjectBuilder &metaObjectBuilder() const;
    qmlbind_interface_handlers handlers() const;
    QHash<int, Method> methodMap() const;
    QHash<int, Property> propertyMap() const;

private:

    qmlbind_class_handle mClassHandle;
    qmlbind_interface_handlers mHandlers;
    QHash<int, Method> mMethodMap;
    QHash<int, Property> mPropertyMap;

    QMetaObjectBuilder mBuilder;
};

} // namespace QmlBind
