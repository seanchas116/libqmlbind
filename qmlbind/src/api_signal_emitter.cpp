#include "qmlbind/signal_emitter.h"
#include "signalemitter.h"
#include "engine.h"

using namespace QmlBind;

extern "C" {

qmlbind_signal_emitter *qmlbind_signal_emitter_new(const qmlbind_value *wrapper) {
    return new SignalEmitter(qobject_cast<Wrapper*>(wrapper->toQObject()));
}

void qmlbind_signal_emitter_emit(qmlbind_signal_emitter *self, const char *signal_name, int argc, const qmlbind_value *const *argv)
{
    self->emitSignal(signal_name, argc, argv);
}

qmlbind_engine *qmlbind_signal_emitter_get_engine(const qmlbind_signal_emitter *self)
{
    return self->getEngine();
}

void qmlbind_signal_emitter_release(qmlbind_signal_emitter *self)
{
    delete self;
}

}
