#include "interface.h"
#include <stdexcept>

namespace QmlBind {

Interface::Interface(const char *className, void *classHandle, qmlbind_interface_handlers handlers) :
    mClassHandle(classHandle),
    mHandlers(handlers)
{
    mBuilder.setClassName(className);
}

static QByteArray methodSignature(const char *name, int arity)
{
    QByteArray sig;
    sig += name;
    sig += "(";
    for (int i = 0; i < arity; ++i) {
        if (i != 0) {
            sig += ",";
        }
        sig += "QJSValue";
    }
    sig += ")";
    return sig;
}

QMetaMethodBuilder Interface::addMethod(void *handle, const char *name, int arity)
{
    QMetaMethodBuilder method = mBuilder.addMethod(methodSignature(name, arity), "QJSValue");

    Method methodInfo;
    methodInfo.arity = arity;
    methodInfo.handle = handle;

    mMethodMap[method.index()] = methodInfo;

    return method;
}

QMetaMethodBuilder Interface::addSignal(const char *name, int arity)
{
    return mBuilder.addSignal(methodSignature(name, arity));
}

QMetaPropertyBuilder Interface::addProperty(void *getterHandle, void *setterHandle, const char *name, int notifySignalIndex)
{
    QMetaPropertyBuilder property = mBuilder.addProperty(name, "QJSValue", notifySignalIndex);

    property.setReadable(getterHandle != 0);
    property.setWritable(setterHandle != 0);

    Property propertyInfo;
    propertyInfo.getterHandle = getterHandle;
    propertyInfo.setterHandle = setterHandle;

    mPropertyMap[property.index()] = propertyInfo;

    return property;
}

void *Interface::classHandle() const
{
    return mClassHandle;
}

const QMetaObjectBuilder *Interface::metaObjectBuilder() const
{
    return &mBuilder;
}

qmlbind_interface_handlers Interface::handlers() const
{
    return mHandlers;
}

QHash<int, Interface::Method> Interface::methodMap() const
{
    return mMethodMap;
}

QHash<int, Interface::Property> Interface::propertyMap() const
{
    return mPropertyMap;
}

} // namespace QmlBind
