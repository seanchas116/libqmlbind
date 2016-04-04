#include "qmlbind/plugin.h"
#include "engine.h"
#include <QPluginLoader>

qmlbind_plugin *qmlbind_plugin_new(const char *filename)
{
    return new QPluginLoader(filename);
}

void qmlbind_plugin_release(qmlbind_plugin *self)
{
    delete self;
}

qmlbind_string *qmlbind_plugin_get_error_string(qmlbind_plugin *self)
{
    if (self->instance()) {
        return nullptr;
    } else {
        return new QByteArray(self->errorString().toUtf8());
    }
}

qmlbind_value *qmlbind_plugin_get_instance(qmlbind_plugin *self, qmlbind_engine *engine)
{
    return new QJSValue(engine->newQObject(self->instance()));
}
