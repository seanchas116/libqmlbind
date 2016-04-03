#include "qmlbind/signal_emitter.h"
#include "signalemitter.h"
#include "engine.h"
#include <QQmlEngine>
#include <QQmlContext>

using namespace QmlBind;

extern "C" {

void qmlbind_signal_emitter_emit(qmlbind_signal_emitter *self, const char *signal_name, int argc, const qmlbind_value *const *argv)
{
    self->emitSignal(signal_name, argc, argv);
}

qmlbind_engine *qmlbind_signal_emitter_get_engine(const qmlbind_signal_emitter *self)
{
    return qobject_cast<Engine *>(QQmlEngine::contextForObject(self->wrapper())->engine());
}

void qmlbind_signal_emitter_release(qmlbind_signal_emitter *self)
{
    delete self;
}

}
