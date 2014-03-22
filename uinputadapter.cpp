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

#include "uinputadapter.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/uinput.h>

#include <QDebug>
#include <QMetaEnum>

UinputAdapter::UinputAdapter(QObject *parent) :
    QObject(parent),
    _fd(-1)
{
}

void UinputAdapter::createDevice(QString name) {
    if (_fd < 0) {
        qDebug("Opening uinput device.");

        _fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

        if (_fd >= 0) {
            qDebug("Successfully opened device.");

            int ret = ioctl(_fd, UI_SET_EVBIT, EV_KEY);
            ret = ioctl(_fd, UI_SET_EVBIT, EV_SYN);
            ret = ioctl(_fd, UI_SET_EVBIT, EV_ABS);
            ret = ioctl(_fd, UI_SET_ABSBIT, ABS_X);
            ret = ioctl(_fd, UI_SET_ABSBIT, ABS_Y);
            ret = ioctl(_fd, UI_SET_ABSBIT, ABS_RX);
            ret = ioctl(_fd, UI_SET_ABSBIT, ABS_RY);

            QMetaObject mo = UinputAdapter::staticMetaObject;
            int enumIdx = mo.indexOfEnumerator("Keys");
            QMetaEnum keysMetaEnum = mo.enumerator(enumIdx);
            for (int i = 0; i < keysMetaEnum.keyCount(); i++) {
                ret = ioctl(_fd, UI_SET_KEYBIT, keysMetaEnum.value(i));
            }

            struct uinput_user_dev uidev;
            memset(&uidev, 0, sizeof(uidev));
            snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, name.toLocal8Bit().constData());
            uidev.id.bustype = 0;
            uidev.id.vendor  = 0;
            uidev.id.product = 0;
            uidev.id.version = 0;
            uidev.absmin[ABS_X] = -128;
            uidev.absmax[ABS_X] = 127;
            uidev.absmin[ABS_Y] = -128;
            uidev.absmax[ABS_Y] = 127;
            uidev.absmin[ABS_RX] = -128;
            uidev.absmax[ABS_RX] = 127;
            uidev.absmin[ABS_RY] = -128;
            uidev.absmax[ABS_RY] = 127;
            ret = write(_fd, &uidev, sizeof(uidev));

            ret = ioctl(_fd, UI_DEV_CREATE);
        }
    }
}

int UinputAdapter::destroyDevice() {
    if (_fd < 0) {
        qDebug("Uinput not initialized.");
        return -1;
    }

    int ret = ioctl(_fd, UI_DEV_DESTROY);
    _fd = -1;
    return ret;
}

int UinputAdapter::emitClick(int keyId, bool val) {
    if (_fd < 0) {
        qDebug("Uinput not initialized.");
        return -1;
    }

    struct input_event ev;
    memset(&ev, 0, sizeof(ev));

    ev.type = EV_KEY;
    ev.code = keyId;
    ev.value = val ? 1 : 0;

    write(_fd, &ev, sizeof(ev));
    syn();
}

int UinputAdapter::emitRxRyEvent(int x, int y) {
    if (_fd < 0) {
        qDebug("Uinput not initialized.");
        return -1;
    }

    struct input_event ev[2];
    memset(ev, 0, sizeof(ev));

    ev[0].type = EV_ABS;
    ev[0].code = ABS_RX;
    ev[0].value = x;
    ev[1].type = EV_ABS;
    ev[1].code = ABS_RY;
    ev[1].value = y;

    write(_fd, ev, sizeof(ev));
    syn();
}

int UinputAdapter::emitXYEvent(int x, int y) {
    if (_fd < 0) {
        qDebug("Uinput not initialized.");
        return -1;
    }

    struct input_event ev[2];
    memset(ev, 0, sizeof(ev));

    ev[0].type = EV_ABS;
    ev[0].code = ABS_X;
    ev[0].value = x;
    ev[1].type = EV_ABS;
    ev[1].code = ABS_Y;
    ev[1].value = y;

    write(_fd, ev, sizeof(ev));
    syn();
}

QString UinputAdapter::keysEnumToString(Keys val) {
    QMetaObject mo = UinputAdapter::staticMetaObject;
    int enumIdx = mo.indexOfEnumerator("Keys");
    QMetaEnum keysMetaEnum = mo.enumerator(enumIdx);
    return QString(keysMetaEnum.valueToKey(val)).toUpper();
}

int UinputAdapter::keysStringToEnum(QString val) {
    QMetaObject mo = UinputAdapter::staticMetaObject;
    int enumIdx = mo.indexOfEnumerator("Keys");
    QMetaEnum keysMetaEnum = mo.enumerator(enumIdx);
    return keysMetaEnum.keyToValue(val.toUpper().toLocal8Bit().data());
}

int UinputAdapter::syn() {
    struct input_event ev;
    memset(&ev, 0, sizeof(ev));

    ev.type = EV_SYN;
    ev.code = SYN_REPORT;
    ev.value = 0;

    return write(_fd, &ev, sizeof(ev));
}
