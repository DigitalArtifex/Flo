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

#ifndef QKLIPPERCPUINFO_H
#define QKLIPPERCPUINFO_H

#include <QObject>

class QKlipperSystem;
class QKlipperConsole;

/*!
 * \brief Filled by machine.system_info
 */
class QKlipperCpuInfo
{
        friend QKlipperSystem;
        friend QKlipperConsole;
    public:
        QKlipperCpuInfo() = default;
        ~QKlipperCpuInfo() = default;

        QKlipperCpuInfo(const QKlipperCpuInfo &value)
        {
            m_bitCount = value.m_bitCount;
            m_cpuCount = value.m_cpuCount;
            m_coreUsage = value.m_coreUsage;
            m_usage = value.m_usage;
            m_description = value.m_description;
            m_hardwareDescription = value.m_hardwareDescription;
            m_memoryUnits = value.m_memoryUnits;
            m_totalMemory = value.m_totalMemory;
            m_model = value.m_model;
            m_processor = value.m_processor;
            m_temp = value.m_temp;
            m_serialNumber = value.m_serialNumber;
        }

        QKlipperCpuInfo &operator=(const QKlipperCpuInfo &value)
        {
            m_bitCount = value.m_bitCount;
            m_cpuCount = value.m_cpuCount;
            m_coreUsage = value.m_coreUsage;
            m_usage = value.m_usage;
            m_description = value.m_description;
            m_hardwareDescription = value.m_hardwareDescription;
            m_memoryUnits = value.m_memoryUnits;
            m_totalMemory = value.m_totalMemory;
            m_model = value.m_model;
            m_processor = value.m_processor;
            m_temp = value.m_temp;
            m_serialNumber = value.m_serialNumber;

            return *this;
        }

        bool operator==(const QKlipperCpuInfo &value)
        {
            if(m_bitCount != value.m_bitCount) return false;
            if(m_cpuCount != value.m_cpuCount) return false;
            if(m_coreUsage != value.m_coreUsage) return false;
            if(m_usage != value.m_usage) return false;
            if(m_description != value.m_description) return false;
            if(m_hardwareDescription != value.m_hardwareDescription) return false;
            if(m_memoryUnits != value.m_memoryUnits) return false;
            if(m_totalMemory != value.m_totalMemory) return false;
            if(m_model != value.m_model) return false;
            if(m_processor != value.m_processor) return false;
            if(m_temp != value.m_temp) return false;
            if(m_serialNumber != value.m_serialNumber) return false;

            return true;
        }

        bool operator!=(const QKlipperCpuInfo &value) { return !(*this == value); }

        qint32 cpuCount() const { return m_cpuCount; }

        qint32 bitCount() const { return m_bitCount; }

        qint64 totalMemory() const { return m_totalMemory; }

        qreal temp() const { return m_temp; }

        qreal usage() const { return m_usage; }

        QString processor() const { return m_processor; }

        QString description() const { return m_description; }

        QString serialNumber() const { return m_serialNumber; }

        QString hardwareDescription() const { return m_hardwareDescription; }

        QString model() const { return m_model; }

        QString memoryUnits() const { return m_memoryUnits; }

        QList<qreal> coreUsage() const { return m_coreUsage; }

    protected:
        void setCpuCount(qint32 cpuCount) { m_cpuCount = cpuCount; }

        void setBitCount(qint32 bitCount) { m_bitCount = bitCount; }

        void setTotalMemory(qint64 totalMemory) { m_totalMemory = totalMemory; }

        void setTemp(qreal temp) { m_temp = temp; }

        void setUsage(qreal usage) { m_usage = usage; }

        void setProcessor(const QString &processor) { m_processor = processor; }

        void setDescription(const QString &description) { m_description = description; }

        void setSerialNumber(const QString &serialNumber) { m_serialNumber = serialNumber; }

        void setHardwareDescription(const QString &hardwareDescription) { m_hardwareDescription = hardwareDescription; }

        void setModel(const QString &model) { m_model = model; }

        void setMemoryUnits(const QString &memoryUnits) { m_memoryUnits = memoryUnits; }

        void setCoreUsage(const QList<qreal> &coreUsage) { m_coreUsage = coreUsage; }

    private:
        qint32 m_cpuCount = 0;
        qint32 m_bitCount = 0;
        qint64 m_totalMemory = 0;

        qreal m_temp = 0;
        qreal m_usage = 0;

        QString m_processor;
        QString m_description;
        QString m_serialNumber;
        QString m_hardwareDescription;
        QString m_model;
        QString m_memoryUnits;

        QList<qreal> m_coreUsage;
};

#endif // QKLIPPERCPUINFO_H
