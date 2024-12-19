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
    public:
        QKlipperPosition() = default;
        ~QKlipperPosition() = default;

        QKlipperPosition(const QKlipperPosition &value)
        {
            m_position = value.m_position;
        }

        qreal &operator[](const QString &name)
        {
            return m_position[name];
        }

        QKlipperPosition &operator=(const QKlipperPosition &value)
        {
            m_position = value.m_position;

            return *this;
        }

        bool operator==(const QKlipperPosition &value) const
        {
            if(m_position == value.m_position) return true;

            return false;
        }

        bool operator!=(const QKlipperPosition &value) const { return !(*this == value); }

        qreal x() const { return m_position["x"]; }
        qreal y() const { return m_position["y"]; }
        qreal z() const { return m_position["z"]; }
        qreal e() const { return m_position["e"]; }

        qreal position(const QString &name, qreal defaultValue = 0.0) const
        {
            if(m_position.contains(name))
                return m_position[name];

            return defaultValue;
        }

    private:
        QMap<QString, qreal> m_position;
};

Q_DECLARE_METATYPE(QKlipperPosition)

#endif // QKLIPPERPOSITION_H
