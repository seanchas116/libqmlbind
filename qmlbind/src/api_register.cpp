#include "typeregisterer.h"
#include "qmlbind/register.h"

using namespace QmlBind;

extern "C" {

int qmlbind_register_type(
    const qmlbind_metaobject *metaobject,
    const char *uri,
    int versionMajor, int versionMinor,
    const char *qmlName)
{
    return TypeRegisterer::instance().registerType(*metaobject, uri, versionMajor, versionMinor, qmlName);
}

}
