#include "qtquick2controlsapplicationviewer.h"

#include <QtQml>

#include "btconnector.h"
#include "settingsadapter.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    QCoreApplication::setOrganizationName("ruedigergad.com");
    QCoreApplication::setOrganizationDomain("ruedigergad.com");
    QCoreApplication::setApplicationName("qzeecontrol2");

    qmlRegisterType<BtConnector>("QZeeControl2", 1, 0, "BtConnector");
    qmlRegisterType<SettingsAdapter>("QZeeControl2", 1, 0, "SettingsAdapter");

    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/qqc/main.qml"));
    viewer.show();

    return app.exec();
}
