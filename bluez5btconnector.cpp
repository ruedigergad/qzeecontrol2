#include "bluez5btconnector.h"

#include <QDBusArgument>
#include <QDBusInterface>
#include <QDebug>

Bluez5BtConnector::Bluez5BtConnector(QObject *parent) :
    QObject(parent)
{
    qDebug("Bluez5BtConnector constructor...");

    QDBusInterface manager("org.bluez", "/", "org.freedesktop.DBus.ObjectManager", QDBusConnection::systemBus());
    QDBusMessage objectsMessage = manager.call("GetManagedObjects");
    qDebug() << objectsMessage;

    const QDBusArgument argument = objectsMessage.arguments().at(0).value<QDBusArgument>();
    if (argument.currentType() == QDBusArgument::MapType) {
        argument.beginMap();
        while ( !argument.atEnd() ) {
                QString key;
                QList<QVariant> value;

                argument.beginMapEntry();
                argument >> key >> value;
                argument.endMapEntry();
                qDebug() << "Key:" << key << "\n  Value:" << value;

                if (value.contains(QVariant(QString ("org.bluez.Adapter1")))) {
                    qDebug() << "Found bluetooth adapter:" << key;

                    _adapterPath = key;

                    QDBusConnection conn = QDBusConnection::systemBus();
                    conn.connect("org.bluez", "", "org.freedesktop.DBus.Properties", "PropertiesChanged",
                                         this, SLOT(_propertiesChanged(QDBusMessage)));

                    break;

                }
            }
        argument.endMap();
    }

}

void Bluez5BtConnector::startDiscovery() {
    qDebug("Starting discovery...");
    QDBusInterface adapter("org.bluez", _adapterPath, "org.bluez.Adapter1", QDBusConnection::systemBus());
    adapter.call("StartDiscovery");
}

void Bluez5BtConnector::_propertiesChanged(QDBusMessage msg) {
    qDebug() << "Adapter properties changed:" << msg;
}
