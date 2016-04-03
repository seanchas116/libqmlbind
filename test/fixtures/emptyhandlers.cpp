#include "emptyhandlers.h"

qmlbind_backref *newObject(qmlbind_backref *, qmlbind_signal_emitter *)
{
    return nullptr;
}

qmlbind_value *invokeMethod(qmlbind_engine *, qmlbind_backref *, const char *, int, qmlbind_value **)
{
    return qmlbind_value_new_undefined();
}

qmlbind_value *invokeGetter(qmlbind_engine *, qmlbind_backref *, const char *)
{
    return qmlbind_value_new_undefined();
}

void invokeSetter(qmlbind_engine *, qmlbind_backref *, const char *, qmlbind_value *)
{
}

void deleteObject(qmlbind_backref *)
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
