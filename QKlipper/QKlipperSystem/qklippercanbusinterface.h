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

#ifndef QKLIPPERCANBUSINTERFACE_H
#define QKLIPPERCANBUSINTERFACE_H

#include <QVariant>

class QKlipperConsole;
class QKlipperCanBusInterface
{
        friend QKlipperConsole;
    public:
        QKlipperCanBusInterface() = default;
        ~QKlipperCanBusInterface() = default;

        QKlipperCanBusInterface(const QKlipperCanBusInterface &interface)
        {
            m_uuid = interface.m_uuid;
            m_application = interface.m_application;
        }

        QKlipperCanBusInterface &operator=(const QKlipperCanBusInterface &interface)
        {
            m_uuid = interface.m_uuid;
            m_application = interface.m_application;

            return *this;
        }

        bool operator==(const QKlipperCanBusInterface &interface) const
        {
            if(m_uuid != interface.m_uuid) return false;
            if(m_application != interface.m_application) return false;

            return true;
        }

        bool operator!=(const QKlipperCanBusInterface &interface) const
        {
            if(m_uuid == interface.m_uuid) return false;
            if(m_application == interface.m_application) return false;

            return true;
        }

        QString uuid() const { return m_uuid; }

        QString application() const { return m_application; }

    protected:
        void setApplication(const QString &application) { m_application = application; }
        void setUuid(const QString &uuid) { m_uuid = uuid; }

    private:
        QString m_uuid;
        QString m_application;
};

Q_DECLARE_METATYPE(QKlipperCanBusInterface)
#endif // QKLIPPERCANBUSINTERFACE_H
