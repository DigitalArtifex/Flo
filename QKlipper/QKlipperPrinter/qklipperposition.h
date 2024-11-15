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

#ifndef QKLIPPERPOSITION_H
#define QKLIPPERPOSITION_H

#include <QObject>
#include <QMap>
//!  QKlipperPosition class
/*!
  This class holds data on the XYZ position as well as extruders. For extruders other than "extruder0", use the
  position("e#") method
*/
class QKlipperPosition
{
    Q_GADGET
public:
    qreal &operator[](const QString &name);

    bool operator==(const QKlipperPosition &value);
    bool operator==(QKlipperPosition &&value);
    bool operator!=(const QKlipperPosition &value);
    bool operator!=(QKlipperPosition &&value);

    qreal x() const;
    qreal y() const;
    qreal z() const;
    qreal e() const;
    qreal position(const QString &name) const;

private:
    QMap<QString, qreal> m_position;
};

Q_DECLARE_METATYPE(QKlipperPosition)

#endif // QKLIPPERPOSITION_H
