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

#include "settingsadapter.h"

#include <QSettings>

SettingsAdapter::SettingsAdapter(QObject *parent) :
    QObject(parent)
{
}

QString SettingsAdapter::readString(const QString &key, const QString &defaultValue) {
    return QSettings().value(key, defaultValue).toString();
}

void SettingsAdapter::setString(const QString &key, const QString &value) {
    QSettings().setValue(key, value);
}
