#ifndef BLUEZ5BTCONNECTOR_H
#define BLUEZ5BTCONNECTOR_H

#include <QObject>
#include <QDBusArgument>
#include <QDBusMessage>

class Bluez5BtConnector : public QObject
{
    Q_OBJECT
public:
    explicit Bluez5BtConnector(QObject *parent = 0);

signals:
    void deviceFound(QString address);

public slots:
    void startDiscovery();
    void stopDiscovery();

private:
    QString _adapterPath;

    QMap<QString, QString> _unpackMapMessage(const QDBusArgument &arg);

private slots:
    void _propertiesChanged(QDBusMessage msg);

};

#endif // BLUEZ5BTCONNECTOR_H
