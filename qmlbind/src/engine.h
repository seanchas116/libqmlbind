#pragma once

#include <QQmlEngine>

namespace QmlBind {

class Engine : public QQmlEngine
{
    Q_OBJECT
public:
    Engine();

    void addComponent(QQmlComponent *component);
    void scheduleDelete();

signals:

public slots:
    void onComponentRemoved();

private:

    bool mDeleteScheduled;
    QList<QQmlComponent *> mComponents;
};

} // namespace QmlBind
