#include "emptyhandlers.h"

qmlbind_client_object *newObject(qmlbind_client_class *, qmlbind_signal_emitter *)
{
    return nullptr;
}

qmlbind_value *invokeMethod(qmlbind_engine *, qmlbind_client_object *, const char *, int, const qmlbind_value *const *)
{
    return qmlbind_value_new_undefined();
}

qmlbind_value *invokeGetter(qmlbind_engine *, qmlbind_client_object *, const char *)
{
    return qmlbind_value_new_undefined();
}

void invokeSetter(qmlbind_engine *, qmlbind_client_object *, const char *, const qmlbind_value *)
{
}

void deleteObject(qmlbind_client_object *)
{
}

qmlbind_interface_handlers emptyHandlers()
{
    qmlbind_interface_handlers handlers {};
    handlers.new_object = &newObject;
    handlers.call_method = &invokeMethod;
    handlers.set_property = &invokeSetter;
    handlers.get_property = &invokeGetter;
    handlers.delete_object = &deleteObject;
    return handlers;
}
