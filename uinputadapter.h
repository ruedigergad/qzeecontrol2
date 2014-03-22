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

#ifndef UINPUTADAPTER_H
#define UINPUTADAPTER_H

#include <QObject>
#include <QString>

#include <linux/input.h>

class UinputAdapter : public QObject
{
    Q_OBJECT

    Q_ENUMS(Keys)

public:
    explicit UinputAdapter(QObject *parent = 0);

    enum Keys {
        A = KEY_A,
        B = KEY_B,
        C = KEY_C,
        D = KEY_D,
        E = KEY_E,
        F = KEY_F,
        G = KEY_G,
        H = KEY_H,
        I = KEY_I,
        J = KEY_J,
        K = KEY_K,
        L = KEY_L,
        M = KEY_M,
        N = KEY_N,
        O = KEY_O,
        P = KEY_P,
        Q = KEY_Q,
        R = KEY_R,
        S = KEY_S,
        T = KEY_T,
        U = KEY_U,
        V = KEY_V,
        W = KEY_W,
        X = KEY_X,
        Y = KEY_Y,
        Z = KEY_Z,
        UP = KEY_UP,
        DOWN = KEY_DOWN,
        LEFT = KEY_LEFT,
        RIGHT = KEY_RIGHT
    };

    Q_INVOKABLE QString keysEnumToString(Keys val);
    Q_INVOKABLE int keysStringToEnum(QString val);

signals:

public slots:
    void createDevice(QString name);
    int destroyDevice();

    int emitClick(int keyId, bool val);
    int emitRxRyEvent(int x, int y);
    int emitXYEvent(int x, int y);

private:
    int _fd;

    int syn();
};

#endif // UINPUTADAPTER_H
