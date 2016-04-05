#include "exporter.h"
#include <stdexcept>
#include <QVector>
#include <QDebug>

namespace QmlBind {

Exporter::Exporter(const char *className, qmlbind_client_class *classObject, qmlbind_interface_handlers interfaceHandlers) :
    mClassObject(classObject),
    mInterfaceHandlers(interfaceHandlers)
{
    if (!interfaceHandlers.call_method) {
        qFatal("qmlbind: call_method handler not specified");
    }
    if (!interfaceHandlers.set_property) {
        qFatal("qmlbind: set_property handler not specified");
    }
    if (!interfaceHandlers.get_property) {
        qFatal("qmlbind: get_property handler not specified");
    }
    if (!interfaceHandlers.new_object) {
        qFatal("qmlbind: new_object handler not specified");
    }
    if (!interfaceHandlers.delete_object) {
        qFatal("qmlbind: delete_object handler not specified");
    }
    mBuilder.setClassName(className);
}

std::unique_ptr<QMetaObject, decltype(&free)> Exporter::toMetaObject() const {
    return std::unique_ptr<QMetaObject, decltype(&free)>(mBuilder.toMetaObject(), free);
}

QByteArray Exporter::methodSignature(const char *name, int arity)
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



void Exporter::addMethod(const char *name, int arity)
{
    QMetaMethodBuilder method = mBuilder.addMethod(Exporter::methodSignature(name, arity), "QJSValue");

    Method methodInfo;
    methodInfo.arity = arity;
    methodInfo.name = name;

    mMethodMap[method.index()] = methodInfo;
}

void Exporter::addSignal(const char *name, const QList<QByteArray> &args)
{
    QMetaMethodBuilder method = mBuilder.addSignal(Exporter::methodSignature(name, args.size()));
    method.setParameterNames(args);

    mSignalIndexMap[name] = method.index();
}

void Exporter::addProperty(const char *name, const char *notifier)
{
    if (!mSignalIndexMap.contains(notifier)) {
        qWarning() << "signal" << notifier << "not yet added";
    }
    QMetaPropertyBuilder property = mBuilder.addProperty(name, "QJSValue", mSignalIndexMap[notifier]);

    property.setReadable(true);
    property.setWritable(true);

    Property propertyInfo;
    propertyInfo.name = name;

    mPropertyMap[property.index()] = propertyInfo;
}

} // namespace QmlBind
