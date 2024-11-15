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

#ifndef QKLIPPERSDINFO_H
#define QKLIPPERSDINFO_H

#include <QObject>
class QKlipperSystem;
class QKlipperConsole;
/*!
 * \brief Filled by machine.system_info
 */
class QKlipperSdInfo : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperSdInfo(QObject *parent = nullptr);

    QKlipperSdInfo(const QKlipperSdInfo &value);
    QKlipperSdInfo(QKlipperSdInfo &&value);
    QKlipperSdInfo &operator=(const QKlipperSdInfo &value);
    QKlipperSdInfo &operator=(QKlipperSdInfo &&value);
    bool operator==(const QKlipperSdInfo &value);
    bool operator==(QKlipperSdInfo &&value);
    bool operator!=(const QKlipperSdInfo &value);
    bool operator!=(QKlipperSdInfo &&value);

    qint64 totalBytes() const;

    qint64 usedBytes() const;

    qint64 availableBytes() const;

    QString manufacturerId() const;

    QString manufacturer() const;

    QString oemId() const;

    QString productName() const;

    QString productRevision() const;

    QString serialNumber() const;

    QString manufacturerDate() const;

    QString capacityString() const;

public slots:

    void setTotalBytes(qint64 totalBytes);

    void setUsedBytes(qint64 usedBytes);

    void setAvailableBytes(qint64 availableBytes);

    void setManufacturerId(const QString &manufacturerId);

    void setManufacturer(const QString &manufacturer);

    void setOemId(const QString &oemId);

    void setProductName(const QString &productName);

    void setProductRevision(const QString &productRevision);

    void setSerialNumber(const QString &serialNumber);

    void setManufacturerDate(const QString &manufacturerDate);

    void setCapacityString(const QString &capacityString);

signals:
    void totalBytesChanged();
    void usedBytesChanged();
    void availableBytesChanged();
    void manufacturerIdChanged();
    void manufacturerChanged();
    void oemIdChanged();
    void productNameChanged();
    void productRevisionChanged();
    void serialNumberChanged();
    void manufacturerDateChanged();
    void capacityStringChanged();

private:
    qint64 m_totalBytes = 0;
    qint64 m_usedBytes = 0;
    qint64 m_availableBytes = 0;

    QString m_manufacturerId;
    QString m_manufacturer;
    QString m_oemId;
    QString m_productName;
    QString m_productRevision;
    QString m_serialNumber;
    QString m_manufacturerDate;
    QString m_capacityString;

    Q_PROPERTY(qint64 totalBytes READ totalBytes WRITE setTotalBytes NOTIFY totalBytesChanged FINAL)
    Q_PROPERTY(qint64 usedBytes READ usedBytes WRITE setUsedBytes NOTIFY usedBytesChanged FINAL)
    Q_PROPERTY(qint64 availableBytes READ availableBytes WRITE setAvailableBytes NOTIFY availableBytesChanged FINAL)
    Q_PROPERTY(QString manufacturerId READ manufacturerId WRITE setManufacturerId NOTIFY manufacturerIdChanged FINAL)
    Q_PROPERTY(QString manufacturer READ manufacturer WRITE setManufacturer NOTIFY manufacturerChanged FINAL)
    Q_PROPERTY(QString oemId READ oemId WRITE setOemId NOTIFY oemIdChanged FINAL)
    Q_PROPERTY(QString productName READ productName WRITE setProductName NOTIFY productNameChanged FINAL)
    Q_PROPERTY(QString productRevision READ productRevision WRITE setProductRevision NOTIFY productRevisionChanged FINAL)
    Q_PROPERTY(QString serialNumber READ serialNumber WRITE setSerialNumber NOTIFY serialNumberChanged FINAL)
    Q_PROPERTY(QString manufacturerDate READ manufacturerDate WRITE setManufacturerDate NOTIFY manufacturerDateChanged FINAL)
    Q_PROPERTY(QString capacityString READ capacityString WRITE setCapacityString NOTIFY capacityStringChanged FINAL)
};

#endif // QKLIPPERSDINFO_H
