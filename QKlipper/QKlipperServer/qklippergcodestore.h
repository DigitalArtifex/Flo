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

#ifndef QKLIPPERGCODESTORE_H
#define QKLIPPERGCODESTORE_H

#include <QObject>

#include "qklippergcodestorevalue.h"

class QKlipperGCodeStore : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperGCodeStore(QObject *parent = nullptr);

    QList<QKlipperGCodeStoreValue> values() const;
    QKlipperGCodeStoreValue value(qint32 index) const;

public slots:
    void setValues(const QList<QKlipperGCodeStoreValue> &values);
    void setValue(const QKlipperGCodeStoreValue &value);

signals:

    void valuesChanged();

private:
    QList<QKlipperGCodeStoreValue> m_values;
    Q_PROPERTY(QList<QKlipperGCodeStoreValue> values READ values WRITE setValues NOTIFY valuesChanged FINAL)
};

#endif // QKLIPPERGCODESTORE_H
