#include "qmlbind/exporter.h"
#include "exporter.h"
#include "interface.h"
#include "util.h"
#include <private/qmetaobjectbuilder_p.h>
#include <private/qobject_p.h>

using namespace QmlBind;

extern "C" {

qmlbind_exporter qmlbind_exporter_new(qmlbind_backref classHandle, const char *className, qmlbind_interface_handlers handlers)
{

    QSharedPointer<Interface> *interface = newSharedPointer(new Interface(handlers));
    return newSharedPointer(new Exporter(className, Backref(classHandle, *interface)));
}

void qmlbind_exporter_release(qmlbind_exporter exporter)
{
    delete exporter;
}

int qmlbind_exporter_add_method(
    qmlbind_exporter exporter,
    const char *name,
    int arity
)
{
    return (*exporter)->addMethod(name, arity).index();
}

int qmlbind_exporter_add_signal(
    qmlbind_exporter exporter,
    const char *name,
    int arity,
    const char **params
)
{
    QList<QByteArray> paramList;
    for (int i = 0; i < arity; ++i) {
        paramList << params[i];
    }
    return (*exporter)->addSignal(name, paramList).index();
}

int qmlbind_exporter_add_property(qmlbind_exporter exporter,
    const char *name,
    const char *notifierSignal
)
{
    return (*exporter)->addProperty(name, notifierSignal).index();
}

}
