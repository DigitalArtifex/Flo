/*
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERCLIENTIDENTIFIER_H
#define QKLIPPERCLIENTIDENTIFIER_H

#include <QObject>

class QKlipperClientIdentifier
{
    Q_GADGET
public:

    bool operator==(const QKlipperClientIdentifier &value)
    {
        if(name != value.name) return false;
        if(version != value.version) return false;
        if(type != value.type) return false;
        if(url != value.url) return false;

        return true;
    }
    bool operator==(QKlipperClientIdentifier &&value)
    {
        if(name != value.name) return false;
        if(version != value.version) return false;
        if(type != value.type) return false;
        if(url != value.url) return false;

        return true;
    }
    bool operator!=(const QKlipperClientIdentifier &value)
    {
        if (name == value.name &&
            version == value.version &&
            type == value.type && url == value.url
            ) return false;

        return true;
    }
    bool operator!=(QKlipperClientIdentifier &&value)
    {
        if (name == value.name &&
            version == value.version &&
            type == value.type && url == value.url
            ) return false;

        return true;
    }

    QString name;
    QString version;
    QString type;
    QString url;
};

#endif // QKLIPPERCLIENTIDENTIFIER_H
