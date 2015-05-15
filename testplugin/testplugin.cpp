#include "testplugin.h"


TestPlugin::TestPlugin(QObject *parent) :
    QObject(parent)
{
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(testplugin, TestPlugin)
#endif // QT_VERSION < 0x050000
