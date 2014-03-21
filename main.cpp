#include "qtquick2controlsapplicationviewer.h"

#include <QtQml>

#include "btconnector.h"
#include "settingsadapter.h"
#include "uinputadapter.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    QCoreApplication::setOrganizationName("ruedigergad.com");
    QCoreApplication::setOrganizationDomain("ruedigergad.com");
    QCoreApplication::setApplicationName("qzeecontrol2");

    qmlRegisterType<BtConnector>("QZeeControl2", 1, 0, "BtConnector");
    qmlRegisterType<SettingsAdapter>("QZeeControl2", 1, 0, "SettingsAdapter");
    qmlRegisterType<UinputAdapter>("QZeeControl2", 1, 0, "UinputAdapter");

    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/qqc/main.qml"));
    viewer.show();

    return app.exec();
}
