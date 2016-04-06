#include "emptycallbacks.h"

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

qmlbind_client_callbacks emptyCallbacks()
{
    qmlbind_client_callbacks callbacks {};
    callbacks.new_object = &newObject;
    callbacks.call_method = &invokeMethod;
    callbacks.set_property = &invokeSetter;
    callbacks.get_property = &invokeGetter;
    callbacks.delete_object = &deleteObject;
    return callbacks;
}
