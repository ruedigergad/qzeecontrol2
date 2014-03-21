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
        BUTTON_A = KEY_A,
        BUTTON_B = KEY_B,
        BUTTON_C = KEY_C,
        BUTTON_D = KEY_D
    };

signals:

public slots:
    void create(QString name);
    int destroy();

    int emitClick(int keyId, bool val);
    int emitXYEvent(int x, int y);

private:
    int _fd;

    int syn();
};

#endif // UINPUTADAPTER_H
