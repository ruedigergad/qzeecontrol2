/*
 *  Copyright 2014 Ruediger Gad
 *
 *  This file is part of QZeeControl2.
 *
 *  QZeeControl2 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QZeeControl2 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with QZeeControl2.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BTCONNECTOR_H
#define BTCONNECTOR_H

#include <QObject>
#include <QBluetoothAddress>
#include <QBluetoothSocket>

class BtConnector : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected READ connectionStatus NOTIFY connectedChanged)

public:
    explicit BtConnector(QObject *parent = 0);

    ~BtConnector(){
        if(socket)
            delete socket;
    }

    Q_INVOKABLE void connect(QString address, int port);
    bool connectionStatus() {return _connected;}

public slots:
    void disconnect();

signals:
    void connected();
    void connectedChanged(bool val);
    void dataReceived(QByteArray data);
    void disconnected();
    void error(QBluetoothSocket::SocketError errorCode);

private slots:
    void readData();
    void socketConnected();
    void socketDisconnected();

private:
    QBluetoothSocket *socket;

    bool _connected;

    void setConnected(bool val) {
        _connected = val;
        connectedChanged(_connected);
    }

};

#endif // BTCONNECTOR_H
