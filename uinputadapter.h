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

    Q_ENUMS(Buttons)

public:
    explicit UinputAdapter(QObject *parent = 0);

    enum Buttons {
        UINPUT_KEY_A = KEY_A,
        UINPUT_KEY_B = KEY_B,
        UINPUT_KEY_C = KEY_C,
        UINPUT_KEY_D = KEY_D,
        UINPUT_KEY_E = KEY_E,
        UINPUT_KEY_F = KEY_F,
        UINPUT_KEY_G = KEY_G,
        UINPUT_KEY_H = KEY_H,
        UINPUT_KEY_I = KEY_I,
        UINPUT_KEY_J = KEY_J,
        UINPUT_KEY_K = KEY_K,
        UINPUT_KEY_L = KEY_L,
        UINPUT_KEY_M = KEY_M,
        UINPUT_KEY_N = KEY_N,
        UINPUT_KEY_O = KEY_O,
        UINPUT_KEY_P = KEY_P,
        UINPUT_KEY_Q = KEY_Q,
        UINPUT_KEY_R = KEY_R,
        UINPUT_KEY_S = KEY_S,
        UINPUT_KEY_T = KEY_T,
        UINPUT_KEY_U = KEY_U,
        UINPUT_KEY_V = KEY_V,
        UINPUT_KEY_W = KEY_W,
        UINPUT_KEY_X = KEY_X,
        UINPUT_KEY_Y = KEY_Y,
        UINPUT_KEY_Z = KEY_Z,
        UINPUT_KEY_UP = KEY_UP,
        UINPUT_KEY_DOWN = KEY_DOWN,
        UINPUT_KEY_LEFT = KEY_LEFT,
        UINPUT_KEY_RIGHT = KEY_RIGHT,
    };

signals:

public slots:
    void create(QString name);
    int destroy();

    int emitClick(int keyId, bool val);
    int emitRxRyEvent(int x, int y);
    int emitXYEvent(int x, int y);

private:
    int _fd;

    int syn();
};

#endif // UINPUTADAPTER_H
