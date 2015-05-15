#include "qmlbind/signal_emitter.h"
#include "signalemitter.h"
#include "engine.h"
#include <QQmlEngine>
#include <QQmlContext>

using namespace QmlBind;

extern "C" {

void qmlbind_signal_emitter_emit(qmlbind_signal_emitter emitter, const char *signal_name, int argc, qmlbind_value *argv)
{
    emitter->emitSignal(signal_name, argc, argv);
}

qmlbind_engine qmlbind_signal_emitter_get_engine(qmlbind_signal_emitter emitter)
{
    Wrapper *wrapper = emitter->wrapper();
    return qobject_cast<Engine *>(QQmlEngine::contextForObject(wrapper)->engine());
}

void qmlbind_signal_emitter_release(qmlbind_signal_emitter emitter)
{
    delete emitter;
}

}
