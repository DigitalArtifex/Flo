/*!
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

#ifndef QKLIPPERENDSTOPSTATUS_H
#define QKLIPPERENDSTOPSTATUS_H

#include <QObject>
#include <QMap>

//!  QKlipperEndstopStatus class
/*!
  This class provides methods to read the status of all
  end stops sent by klipper in printer.query_endstops
*/
class QKlipperEndstopStatus
{
    Q_GADGET
public:
    /*!
     * Subscript operator
     *
     * \param name The name of the endstop (eg "x")
     *
     * \returns QKlipperEndstopStatus reference
     */
    bool &operator[](const QString &name)
    {
        return m_endstops[name];
    }

    bool operator==(const QKlipperEndstopStatus &value)
    {
        QStringList keys = value.m_endstops.keys();

        foreach(QString key, keys)
        {
            if(!m_endstops.contains(key))
                return false;
            else if(m_endstops[key] != value.endStop(key))
                return false;
        }

        return true;
    }

    bool operator!=(const QKlipperEndstopStatus &value)
    {
        return !(this == &value);
    }

    /*!
     * Convenience function to return the 'x' endstop status
     *
     * \returns QKlipperEndstopStatus reference
     */
    bool x() const
    {
        return m_endstops["x"];
    }

    /*!
     * Convenience function to return the 'y' endstop status
     *
     * \returns QKlipperEndstopStatus reference
     */
    bool y() const
    {
        return m_endstops["y"];
    }

    /*!
     * Convenience function to return the 'z' endstop status
     *
     * \returns QKlipperEndstopStatus reference
     */
    bool z() const
    {
        return m_endstops["z"];
    }

    /*!
     * Convenience function to return the endstop status by name
     *
     * \param name The name of the endstop
     *
     * \returns QKlipperEndstopStatus reference
     */
    bool endStop(const QString &name) const
    {
        return m_endstops[name];
    }

    /*!
     * Checks to see if there is a stored reference for the endstop name
     *
     * \param name The name of the endstop
     *
     * \returns True if the reference exists
     */
    bool contains(const QString &name) const
    {
        return m_endstops.contains(name);
    }

private:
    QMap<QString, bool> m_endstops;
};

Q_DECLARE_METATYPE(QKlipperEndstopStatus)
#endif // QKLIPPERENDSTOPSTATUS_H
