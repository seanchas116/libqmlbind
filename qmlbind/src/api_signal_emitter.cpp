#include "qmlbind/signal_emitter.h"
#include "signalemitter.h"

extern "C" {

void qmlbind_signal_emitter_emit(qmlbind_signal_emitter emitter, const char *signal_name, int argc, qmlbind_value *argv)
{
    emitter->emitSignal(signal_name, argc, argv);
}

void qmlbind_signal_emitter_release(qmlbind_signal_emitter emitter)
{
    delete emitter;
}

}
