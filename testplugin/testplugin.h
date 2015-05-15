#pragma once

#include <QObject>

class TestPlugin : public QObject
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "testplugin.json")
#endif // QT_VERSION >= 0x050000

    Q_PROPERTY(int test READ test)

public:
    TestPlugin(QObject *parent = 0);

    int test() const
    {
        return 12345;
    }
};
