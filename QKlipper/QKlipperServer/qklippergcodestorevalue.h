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

#ifndef QKLIPPERGCODESTOREVALUE_H
#define QKLIPPERGCODESTOREVALUE_H

#include <QObject>
#include <QVariant>
#include <QList>

class QKlipperGCodeStoreValue : public QVariant
{
    Q_GADGET
public:
    enum GCodeType {
        Command,
        Response
    };

    bool operator==(const QKlipperGCodeStoreValue &value);
    bool operator!=(const QKlipperGCodeStoreValue &value);

    QString message() const;

    GCodeType gcodeType() const;

    qreal time() const;

    void setMessage(const QString &message);

    void setGcodeType(GCodeType gcodeType);

    void setTime(qreal time);

private:

    QString m_message;
    GCodeType m_gcodeType = Response;
    qreal m_time;
};


Q_DECLARE_METATYPE(QKlipperGCodeStoreValue)
#endif // QKLIPPERGCODESTOREVALUE_H
