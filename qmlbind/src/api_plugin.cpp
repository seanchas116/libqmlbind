#include "qmlbind/plugin.h"
#include "engine.h"
#include <QPluginLoader>

qmlbind_plugin qmlbind_plugin_new(const char *filename)
{
    return new QPluginLoader(filename);
}

void qmlbind_plugin_release(qmlbind_plugin plugin)
{
    delete plugin;
}

qmlbind_string qmlbind_plugin_get_error_string(qmlbind_plugin plugin)
{
    QString error = plugin->errorString();
    if (error.isEmpty()) {
        return 0;
    } else {
        return new QByteArray(plugin->errorString().toUtf8());
    }
}

qmlbind_value qmlbind_plugin_get_instance(qmlbind_plugin plugin, qmlbind_engine engine)
{
    return new QJSValue(engine->newQObject(plugin->instance()));
}
