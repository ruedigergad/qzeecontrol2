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

#include "btconnector.h"

#include <QStringList>

BtConnector::BtConnector(QObject *parent)
    : QObject(parent){
    _connected = false;
    socket = NULL;
}

void BtConnector::connect(QString address, int port){
    qDebug("Trying to connect to: %s--%d", address.toUtf8().constData(), port);

    if(socket)
        delete socket;

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    QObject::connect(socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    QObject::connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SIGNAL(error(QBluetoothSocket::SocketError)));

    qDebug("Connecting...");
    socket->connectToService(QBluetoothAddress(address), port);

    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

void BtConnector::disconnect(){
    if(!socket)
        return;

    if(socket->isOpen())
        socket->close();

    delete socket;
    socket = NULL;
}

void BtConnector::readData(){
    QByteArray data = socket->readAll();
    emit dataReceived(data);
}

void BtConnector::socketConnected() {
    setConnected(true);
    emit connected();
}

void BtConnector::socketDisconnected() {
    setConnected(false);
    emit disconnected();
}
