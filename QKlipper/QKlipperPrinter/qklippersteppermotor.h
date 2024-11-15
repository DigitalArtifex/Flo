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

#ifndef QKLIPPERSTEPPERMOTOR_H
#define QKLIPPERSTEPPERMOTOR_H

#include <QObject>

class QKlipperStepperMotor : public QObject
{
    Q_OBJECT
public:
    explicit QKlipperStepperMotor(QObject *parent = nullptr);

    QString name() const;

    qreal current() const;

    bool enabled() const;

public slots:
    void setName(const QString &name);

    void setCurrent(qreal current);

    void setEnabled(bool enabled);

signals:

    void nameChanged();

    void currentChanged();

    void enabledChanged();

private:
    QString m_name;
    qreal m_current;
    bool m_enabled;

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(qreal current READ current WRITE setCurrent NOTIFY currentChanged FINAL)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged FINAL)
};

#endif // QKLIPPERSTEPPERMOTOR_H
