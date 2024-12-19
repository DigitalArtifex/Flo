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

#ifndef QKLIPPERV412MODE_H
#define QKLIPPERV412MODE_H

#include <QVariant>

class QKlipperV412Mode
{
    public:
        QKlipperV412Mode() = default;
        ~QKlipperV412Mode() = default;

        QKlipperV412Mode(const QKlipperV412Mode &value)
        {
            m_description = value.m_description;
            m_flags = value.m_flags;
            m_format = value.m_format;
            m_resolutions = value.m_resolutions;
        }

        QKlipperV412Mode &operator=(const QKlipperV412Mode &value)
        {
            m_description = value.m_description;
            m_flags = value.m_flags;
            m_format = value.m_format;
            m_resolutions = value.m_resolutions;

            return *this;
        }

        bool operator==(const QKlipperV412Mode &value) const
        {
            if(m_description != value.m_description) return false;
            if(m_flags != value.m_flags) return false;
            if(m_format != value.m_format) return false;
            if(m_resolutions != value.m_resolutions) return false;

            return true;
        }

        bool operator!=(const QKlipperV412Mode &value) const { return !(*this == value); }

        QString description() const { return m_description; }

        QString format() const { return m_format; }

        QStringList flags() const { return m_flags; }

        QStringList resolutions() const { return m_resolutions; }

        void setDescription(const QString &description) { m_description = description; }

        void setFormat(const QString &format) { m_format = format; }

        void setFlags(const QStringList &flags) { m_flags = flags; }

        void setResolutions(const QStringList &resolutions) { m_resolutions = resolutions; }

    private:
        QString m_description;
        QString m_format;

        QStringList m_flags;
        QStringList m_resolutions;
};

Q_DECLARE_METATYPE(QKlipperV412Mode)
#endif // QKLIPPERV412MODE_H
