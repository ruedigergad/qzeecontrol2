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

#ifndef SETTINGSADAPTER_H
#define SETTINGSADAPTER_H

#include <QObject>

class SettingsAdapter : public QObject
{
    Q_OBJECT
public:
    explicit SettingsAdapter(QObject *parent = 0);

    Q_INVOKABLE bool readBoolean(const QString &key, const bool &defaultValue);
    Q_INVOKABLE int readInt(const QString &key, const int &defaultValue);
    Q_INVOKABLE QString readString(const QString &key, const QString &defaultValue);

    Q_INVOKABLE void setBoolean(const QString &key, const bool &value);
    Q_INVOKABLE void setInt(const QString &key, const int &value);
    Q_INVOKABLE void setString(const QString &key, const QString &value);


signals:

public slots:

};

#endif // SETTINGSADAPTER_H
