#include "qtquick2controlsapplicationviewer.h"

#include <QtQml>

#include "bluez5btadapter.h"
#include "btconnector.h"
#include "btdataprocessor.h"
#include "settingsadapter.h"
#include "uinputadapter.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    QCoreApplication::setOrganizationName("ruedigergad.com");
    QCoreApplication::setOrganizationDomain("ruedigergad.com");
    QCoreApplication::setApplicationName("qzeecontrol2");

    qmlRegisterType<Bluez5BtAdapter>("QZeeControl", 2, 0, "Bluez5BtAdapter");
    qmlRegisterType<BtConnector>("QZeeControl", 2, 0, "BtConnector");
    qmlRegisterType<BtDataProcessor>("QZeeControl", 2, 0, "BtDataProcessor");
    qmlRegisterType<SettingsAdapter>("QZeeControl", 2, 0, "SettingsAdapter");
    qmlRegisterType<UinputAdapter>("QZeeControl", 2, 0, "UinputAdapter");

    QtQuick2ControlsApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/qqc/main.qml"));
    viewer.show();

    return app.exec();
}
