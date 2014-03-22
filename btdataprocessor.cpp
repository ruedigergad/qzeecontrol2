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

#include "btdataprocessor.h"

#include <QStringList>

BtDataProcessor::BtDataProcessor(QObject *parent) :
    QObject(parent)
{
    _threshold = 50;

    _up = false;
    _down = false;
    _left = false;
    _right = false;

    _a = false;
    _b = false;
    _c = false;
    _d = false;

    _x = 0;
    _y = 0;
    _oldButtonMap = 0;
}

void BtDataProcessor::processData(QByteArray data) {
    /*
     * Actually it seems like that the first three bytes are used for
     * identifying the "type" of data sent. However, for now using the
     * first seems to suffice.
     */
    if(data.at(0) == 5){
        /*
         * Joystick movement
         *
         * X-Axis: positive values -> right, negative values -> left
         * Y-Axis: positive values -> down, negative values -> up
         */

        setX((int)(signed char) data.at(4));
        setY((int)(signed char) data.at(5));

        emit(stickMoved(_x, _y));

        /*
         * Emulate a digital joystick.
         */
        if(_up && (_y > -threshold())){
            setUp(false);
        }else if(!_up && (_y < -threshold())){
            setUp(true);
        }

        if(_down && (_y < threshold())){
            setDown(false);
        }else if(!_down && (_y > threshold())){
            setDown(true);
        }

        if(_left && (_x > -threshold())){
            setLeft(false);
        }else if(!_left && (_x < -threshold())){
            setLeft(true);
        }

        if(_right && (_x < threshold())){
            setRight(false);
        }else if(!_right && (_x > threshold())){
            setRight(true);
        }
    }else if(data.at(0) == 8){
        /*
         * Button presses
         *
         * A -> 0, B -> 1, C -> 2, D ->3
         * At index 3 to 6 (inclusive)
         */

        char buttonMap = 0;

        for(int i = 3; i <= 6; i++){
            for(int b = 0; b <= 3; b++){
                if(data.at(i) == b){
                    buttonMap ^= (1 << b);
                }
            }
        }

        emit(buttonsChanged(buttonMap & 0x01, buttonMap & 0x02, buttonMap & 0x04, buttonMap & 0x08));

        for(int i = 0; i <= 3; i++){
            if(((buttonMap | _oldButtonMap) & (1 << i)) > 0){
                bool val = (buttonMap & (1 << i)) > 0;
                switch (i){
                case 0:
                    setA(val);
                    break;
                case 1:
                    setB(val);
                    break;
                case 2:
                    setC(val);
                    break;
                case 3:
                    setD(val);
                    break;
                }
            }
        }

        _oldButtonMap = buttonMap;
    }

    QStringList outputData;
    outputData << QString::number(_x);
    outputData << QString::number(_y);
    outputData << (_a ? "1" : "0");
    outputData << (_b ? "1" : "0");
    outputData << (_c ? "1" : "0");
    outputData << (_d ? "1" : "0");
    outputData << (_left ? "1" : "0");
    outputData << (_right ? "1" : "0");
    outputData << (_up ? "1" : "0");
    outputData << (_down ? "1" : "0");

    emit dataUpdated(outputData.join(" "));
}
