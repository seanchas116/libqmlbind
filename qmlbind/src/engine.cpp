#include "engine.h"
#include <QQmlComponent>

namespace QmlBind {

Engine::Engine() : QQmlEngine(), mDeleteScheduled(false)
{
}

void Engine::addComponent(QQmlComponent *component)
{
    mComponents << component;
    connect(component, SIGNAL(destroyed(QObject*)), this, SLOT(onComponentRemoved()));
}

void Engine::scheduleDelete()
{
    if (mComponents.size() == 0) {
        delete this;
    }
    mDeleteScheduled = true;
}

void Engine::onComponentRemoved()
{
    mComponents.removeAll(qobject_cast<QQmlComponent *>(sender()));
    if (mComponents.size() == 0) {
        delete this;
    }
}

} // namespace QmlBind
