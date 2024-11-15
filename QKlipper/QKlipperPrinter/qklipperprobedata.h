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

class QKlipperProbeData
{
    Q_GADGET
public:
    explicit QKlipperProbeData(QObject *parent = nullptr);
    ~QKlipperProbeData();

    QString name() const;

    bool isManual() const;

    bool lastQuery() const;

    qreal zPosition() const;

    qreal zPositionLower() const;

    qreal zPositionUpper() const;

    void setName(const QString &name);
    void resetName();

    void setIsManual(bool isManual);
    void resetIsManual();

    void setLastQuery(bool lastQuery);
    void resetLastQuery();

    void setZPosition(qreal zPosition);
    void resetZPosition();

    void setZPositionLower(qreal zPositionLower);
    void resetZPositionLower();

    void setZPositionUpper(qreal zPositionUpper);
    void resetZPositionUpper();

    bool operator==(const QKlipperProbeData &data) const
    {
        if(this->m_name != data.m_name) return false;
        if(this->m_isManual != data.m_isManual) return false;
        if(this->m_lastQuery != data.m_lastQuery) return false;
        if(this->m_zPosition != data.m_zPosition) return false;
        if(this->m_zPositionLower != data.m_zPositionLower) return false;
        if(this->m_zPositionUpper != data.m_zPositionUpper) return false;

        return true;
    }

    bool operator!=(const QKlipperProbeData &data) const
    {
        if(this->m_name == data.m_name &&
            this->m_isManual == data.m_isManual &&
            this->m_lastQuery == data.m_lastQuery &&
            this->m_zPosition == data.m_zPosition &&
            this->m_zPositionLower == data.m_zPositionLower &&
            this->m_zPositionUpper == data.m_zPositionUpper)
            return false;

        return true;
    }

    qreal lastZResult() const;
    void setLastZResult(qreal lastZResult);

private:
    QString m_name;

    bool m_isManual = false;
    bool m_lastQuery = false;

    qreal m_zPosition = 0;
    qreal m_zPositionLower = 0;
    qreal m_zPositionUpper = 0;
    qreal m_lastZResult = 0;

    Q_PROPERTY(QString name READ name WRITE setName FINAL)
    Q_PROPERTY(bool isManual READ isManual WRITE setIsManual FINAL)
    Q_PROPERTY(bool lastQuery READ lastQuery WRITE setLastQuery FINAL)
    Q_PROPERTY(qreal zPosition READ zPosition WRITE setZPosition FINAL)
    Q_PROPERTY(qreal zPositionLower READ zPositionLower WRITE setZPositionLower FINAL)
    Q_PROPERTY(qreal zPositionUpper READ zPositionUpper WRITE setZPositionUpper FINAL)
    Q_PROPERTY(qreal lastZResult READ lastZResult WRITE setLastZResult FINAL)
};

Q_DECLARE_METATYPE(QKlipperProbeData)
#endif // QKLIPPERPROBEDATA_H
