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

#ifndef QKLIPPERPROBEDATA_H
#define QKLIPPERPROBEDATA_H

#include <QObject>
class QKlipperConsole;

class QKlipperProbeData
{
        friend QKlipperConsole;
    public:
        QKlipperProbeData() = default;
        ~QKlipperProbeData() = default;
        QKlipperProbeData &operator=(const QKlipperProbeData &value)
        {
            m_name = value.m_name;
            m_isManual = value.m_isManual;
            m_lastQuery = value.m_lastQuery;
            m_zPosition = value.m_zPosition;
            m_zPositionLower = value.m_zPositionLower;
            m_zPositionUpper = value.m_zPositionUpper;
            m_lastZResult = value.m_lastZResult;

            return *this;
        }

        bool operator==(const QKlipperProbeData &value) const
        {
            if(m_name != value.m_name) return false;
            if(m_isManual != value.m_isManual) return false;
            if(m_lastQuery != value.m_lastQuery) return false;
            if(m_zPosition != value.m_zPosition) return false;
            if(m_zPositionLower != value.m_zPositionLower) return false;
            if(m_zPositionUpper != value.m_zPositionUpper) return false;

            return true;
        }

        bool operator!=(const QKlipperProbeData &value) const { return !(*this == value); }

        QString name() const { return m_name; }

        bool isManual() const { return m_isManual; }

        bool lastQuery() const { return m_lastQuery; }

        qreal zPosition() const { return m_zPosition; }

        qreal zPositionLower() const { return m_zPositionLower; }

        qreal zPositionUpper() const { return m_zPositionUpper; }

        qreal lastZResult() const { return m_lastZResult; }

    protected:
        void setName(const QString &name) { m_name = name; }

        void setIsManual(bool isManual) { m_isManual = isManual; }

        void setLastQuery(bool lastQuery) { m_lastQuery = lastQuery; }

        void setZPosition(qreal zPosition) { m_zPosition = zPosition; }

        void setZPositionLower(qreal zPositionLower) { m_zPositionLower = zPositionLower; }

        void setZPositionUpper(qreal zPositionUpper) { m_zPositionUpper = zPositionUpper; }

        void setLastZResult(qreal lastZResult) { m_lastZResult = lastZResult; }

    private:
        QString m_name;

        bool m_isManual = false;
        bool m_lastQuery = false;

        qreal m_zPosition = 0;
        qreal m_zPositionLower = 0;
        qreal m_zPositionUpper = 0;
        qreal m_lastZResult = 0;
};

Q_DECLARE_METATYPE(QKlipperProbeData)
#endif // QKLIPPERPROBEDATA_H
