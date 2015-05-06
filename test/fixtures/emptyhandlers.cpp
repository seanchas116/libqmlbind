#include "emptyhandlers.h"

qmlbind_backref newObject(qmlbind_backref, qmlbind_signal_emitter)
{
    return nullptr;
}

qmlbind_value invokeMethod(qmlbind_engine, qmlbind_backref, qmlbind_backref, int, qmlbind_value *)
{
    return qmlbind_value_new_undefined();
}

qmlbind_value invokeGetter(qmlbind_engine, qmlbind_backref, qmlbind_backref)
{
    return qmlbind_value_new_undefined();
}

void invokeSetter(qmlbind_engine, qmlbind_backref, qmlbind_backref, qmlbind_value)
{
}

void deleteObject(qmlbind_backref)
{
}

qmlbind_interface_handlers emptyHandlers()
{
    qmlbind_interface_handlers handlers = {
        .new_object = &newObject,
        .call_method = &invokeMethod,
        .set_property = &invokeSetter,
        .get_property = &invokeGetter,
        .delete_object = &deleteObject
    };
    return handlers;
}
