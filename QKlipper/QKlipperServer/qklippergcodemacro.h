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

#ifndef QKLIPPERGCODEMACRO_H
#define QKLIPPERGCODEMACRO_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QVariant>

class QKlipperGCodeMacro : public QVariant
{
    Q_GADGET

public:
    QString macro;
    QString description;
    QString gcode;
    QString replaces;

    bool contains(const QString &key)
    {
        return variables.contains(key);
    }

    bool operator==(const QKlipperGCodeMacro &value)
    {
        if(macro != value.macro ||
            description != value.description ||
            gcode != value.gcode ||
            replaces != value.replaces)
            return false;

        return true;
    }

    bool operator!=(const QKlipperGCodeMacro &value)
    {
        if(macro == value.macro &&
            description == value.description &&
            gcode == value.gcode &&
            replaces == value.replaces)
            return false;

        return true;
    }

    QString &operator[](const QString &key)
    {
        return variables[key];
    }

private:
    QMap<QString,QString> variables;
};


typedef QList<QKlipperGCodeMacro> QKlipperGCodeMacroList;

#endif // QKLIPPERGCODEMACRO_H
