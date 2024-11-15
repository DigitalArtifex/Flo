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
class QKlipperCpuInfo : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperCpuInfo(QObject *parent = nullptr);

    QKlipperCpuInfo(const QKlipperCpuInfo &value);
    QKlipperCpuInfo(QKlipperCpuInfo &&value);
    QKlipperCpuInfo &operator=(const QKlipperCpuInfo &value);
    QKlipperCpuInfo &operator=(QKlipperCpuInfo &&value);
    bool operator==(const QKlipperCpuInfo &value);
    bool operator==(QKlipperCpuInfo &&value);
    bool operator!=(const QKlipperCpuInfo &value);
    bool operator!=(QKlipperCpuInfo &&value);

    qint32 cpuCount() const;

    qint32 bitCount() const;

    qint64 totalMemory() const;

    qreal temp() const;

    qreal usage() const;

    QString processor() const;

    QString description() const;

    QString serialNumber() const;

    QString hardwareDescription() const;

    QString model() const;

    QString memoryUnits() const;

    QList<qreal> coreUsage() const;

private slots:
    void setCpuCount(qint32 cpuCount);
    void resetCpuCount();

    void setBitCount(qint32 bitCount);
    void resetBitCount();

    void setTotalMemory(qint64 totalMemory);
    void resetTotalMemory();

    void setTemp(qreal temp);
    void resetTemp();

    void setUsage(qreal usage);
    void resetUsage();

    void setProcessor(const QString &processor);
    void resetProcessor();

    void setDescription(const QString &description);
    void resetDescription();

    void setSerialNumber(const QString &serialNumber);
    void resetSerialNumber();

    void setHardwareDescription(const QString &hardwareDescription);
    void resetHardwareDescription();

    void setModel(const QString &model);
    void resetModel();

    void setMemoryUnits(const QString &memoryUnits);
    void resetMemoryUnits();

    void setCoreUsage(const QList<qreal> &coreUsage);
    void resetCoreUsage();

signals:
    void cpuCountChanged();
    void bitCountChanged();
    void totalMemoryChanged();
    void tempChanged();
    void usageChanged();
    void processorChanged();
    void descriptionChanged();
    void serialNumberChanged();
    void hardwareDescriptionChanged();
    void modelChanged();
    void memoryUnitsChanged();
    void coreUsageChanged();

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

    Q_PROPERTY(qint32 cpuCount READ cpuCount WRITE setCpuCount RESET resetCpuCount NOTIFY cpuCountChanged FINAL)
    Q_PROPERTY(qint32 bitCount READ bitCount WRITE setBitCount RESET resetBitCount NOTIFY bitCountChanged FINAL)
    Q_PROPERTY(qint64 totalMemory READ totalMemory WRITE setTotalMemory RESET resetTotalMemory NOTIFY totalMemoryChanged FINAL)
    Q_PROPERTY(qreal temp READ temp WRITE setTemp RESET resetTemp NOTIFY tempChanged FINAL)
    Q_PROPERTY(qreal usage READ usage WRITE setUsage RESET resetUsage NOTIFY usageChanged FINAL)
    Q_PROPERTY(QString processor READ processor WRITE setProcessor RESET resetProcessor NOTIFY processorChanged FINAL)
    Q_PROPERTY(QString description READ description WRITE setDescription RESET resetDescription NOTIFY descriptionChanged FINAL)
    Q_PROPERTY(QString serialNumber READ serialNumber WRITE setSerialNumber RESET resetSerialNumber NOTIFY serialNumberChanged FINAL)
    Q_PROPERTY(QString hardwareDescription READ hardwareDescription WRITE setHardwareDescription RESET resetHardwareDescription NOTIFY hardwareDescriptionChanged FINAL)
    Q_PROPERTY(QString model READ model WRITE setModel RESET resetModel NOTIFY modelChanged FINAL)
    Q_PROPERTY(QString memoryUnits READ memoryUnits WRITE setMemoryUnits RESET resetMemoryUnits NOTIFY memoryUnitsChanged FINAL)
    Q_PROPERTY(QList<qreal> coreUsage READ coreUsage WRITE setCoreUsage RESET resetCoreUsage NOTIFY coreUsageChanged FINAL)
};

#endif // QKLIPPERCPUINFO_H
