#include "qmlbind/component.h"
#include "engine.h"
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>

using namespace QmlBind;

extern "C" {

qmlbind_component *qmlbind_component_new(qmlbind_engine *engine)
{
    return new QQmlComponent(engine);
}

void qmlbind_component_release(qmlbind_component *component)
{
    delete component;
}

void qmlbind_component_load_path(qmlbind_component *component, const char *path)
{
    component->loadUrl(QUrl::fromLocalFile(path));
}

void qmlbind_component_set_data(qmlbind_component *component, const char *data, const char *path)
{
    component->setData(data, QUrl::fromLocalFile(path));
}

qmlbind_string *qmlbind_component_get_error_string(qmlbind_component *component)
{
    QString str = component->errorString();

    if (str.isEmpty()) {
        return 0;
    }
    else {
        return new QByteArray(str.toUtf8());
    }
}

qmlbind_value *qmlbind_component_create(qmlbind_component *component)
{
    QObject *object = component->create();
    if (!object) {
        return new QJSValue(QJSValue::UndefinedValue);
    }
    QQmlEngine::setObjectOwnership(object, QQmlEngine::JavaScriptOwnership);
    return new QJSValue(QQmlEngine::contextForObject(object)->engine()->newQObject(object));
}

}
