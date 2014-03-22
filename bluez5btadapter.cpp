#include "bluez5btadapter.h"

#include <QDBusArgument>
#include <QDBusInterface>
#include <QDebug>

Bluez5BtAdapter::Bluez5BtAdapter(QObject *parent) :
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

void Bluez5BtAdapter::startDiscovery() {
    qDebug("Starting discovery...");
    QDBusInterface adapter("org.bluez", _adapterPath, "org.bluez.Adapter1", QDBusConnection::systemBus());
    adapter.call("StartDiscovery");
}

void Bluez5BtAdapter::stopDiscovery() {
    qDebug("Stopping discovery...");
    QDBusInterface adapter("org.bluez", _adapterPath, "org.bluez.Adapter1", QDBusConnection::systemBus());
    adapter.call("StopDiscovery");
}

void Bluez5BtAdapter::_propertiesChanged(QDBusMessage msg) {
    qDebug() << "Adapter properties changed:" << msg;

    if (msg.arguments().at(0).toString() == "org.bluez.Device1") {
        qDebug() << "Found a device:" << msg.path();

        //FIXME: This is quite brute force and ugly.
        //       There has to be a better way to get the address of a discovered device?!
        QString address = msg.path().split("dev_").last().split("_").join(":");
        qDebug() << "Got address:" << address;
        emit deviceFound(address);

        const QDBusArgument argument = msg.arguments().at(1).value<QDBusArgument>();

        if (argument.currentType() == QDBusArgument::MapType) {
            qDebug("We have a map message.");

            argument.beginMap();
            while ( !argument.atEnd() ) {
                    QString key;
                    QVariant value;

                    argument.beginMapEntry();
                    argument >> key >> value;
                    argument.endMapEntry();
                    qDebug() << "Key:" << key << "\n  Value:" << value;
            }
            argument.endMap();
        }
    }
}
