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

#ifndef BTDATAPROCESSOR_H
#define BTDATAPROCESSOR_H

#include <QObject>

class BtDataProcessor : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int threshold READ threshold NOTIFY thresholdChanged WRITE setThreshold)

    Q_PROPERTY(bool up READ up NOTIFY upChanged)
    Q_PROPERTY(bool down READ down NOTIFY downChanged)
    Q_PROPERTY(bool left READ left NOTIFY leftChanged)
    Q_PROPERTY(bool right READ right NOTIFY rightChanged)

    Q_PROPERTY(bool a READ a NOTIFY aChanged)
    Q_PROPERTY(bool b READ b NOTIFY bChanged)
    Q_PROPERTY(bool c READ c NOTIFY cChanged)
    Q_PROPERTY(bool d READ d NOTIFY dChanged)

    Q_PROPERTY(int x READ x NOTIFY xChanged)
    Q_PROPERTY(int y READ y NOTIFY yChanged)

public:
    explicit BtDataProcessor(QObject *parent = 0);

    int threshold(void){return _threshold;}
    void setThreshold(int val){
        _threshold = val;
        thresholdChanged(_threshold);
    }

    bool up(){return _up;}
    bool down(){return _down;}
    bool left(){return _left;}
    bool right(){return _right;}

    bool a(){return _a;}
    bool b(){return _b;}
    bool c(){return _c;}
    bool d(){return _d;}

    int x(){return _x;}
    int y(){return _y;}

signals:
    void stickMoved(int x, int y);
    void buttonsChanged(bool a, bool b, bool c, bool d);

    void thresholdChanged(int val);

    void upChanged(bool val);
    void downChanged(bool val);
    void leftChanged(bool val);
    void rightChanged(bool val);

    void aChanged(bool val);
    void bChanged(bool val);
    void cChanged(bool val);
    void dChanged(bool val);

    void xChanged(int val);
    void yChanged(int val);

    void dataUpdated(QString data);

public slots:
    void processData(QByteArray data);

private:
    int _threshold;

    bool _up;
    bool _down;
    bool _left;
    bool _right;

    bool _a;
    bool _b;
    bool _c;
    bool _d;

    int _x;
    int _y;

    char _oldButtonMap;

    void setA(bool val){
        _a = val;
        aChanged(_a);
    }
    void setB(bool val){
        _b = val;
        bChanged(_b);
    }
    void setC(bool val){
        _c = val;
        cChanged(_c);
    }
    void setD(bool val){
        _d = val;
        dChanged(_d);
    }

    void setX(int val){
        _x = val;
        xChanged(_x);
    }
    void setY(int val){
        _y = val;
        yChanged(_y);
    }

    void setUp(bool val){
        _up = val;
        upChanged(_up);
    }
    void setDown(bool val){
        _down = val;
        downChanged(_down);
    }
    void setLeft(bool val){
        _left = val;
        leftChanged(_left);
    }
    void setRight(bool val){
        _right = val;
        rightChanged(_right);
    }

};

#endif // BTDATAPROCESSOR_H
