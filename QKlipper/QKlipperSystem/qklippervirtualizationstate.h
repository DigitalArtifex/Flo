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

#ifndef QKLIPPERVIRTUALIZATIONSTATE_H
#define QKLIPPERVIRTUALIZATIONSTATE_H

#include <QObject>
class QKlipperSystem;
class QKlipperConsole;

/*!
 * \brief Filled by machine.system_info
 */
class QKlipperVirtualizationState : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperVirtualizationState(QObject *parent = nullptr);

    bool operator==(const QKlipperVirtualizationState &value);
    bool operator!=(const QKlipperVirtualizationState &value);

    QString type() const;

    QString identifier() const;

public slots:
    void setType(const QString &type);

    void setIdentifier(const QString &identifier);

private slots:

signals:

    void typeChanged();

    void identifierChanged();

private:
    QString m_type;
    QString m_identifier;
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier NOTIFY identifierChanged FINAL)
};

#endif // QKLIPPERVIRTUALIZATIONSTATE_H
