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

class QKlipperV412Mode : public QVariant
{
public:
    QKlipperV412Mode();
    QKlipperV412Mode(const QKlipperV412Mode &value);

    QKlipperV412Mode &operator=(const QKlipperV412Mode &value);
    bool operator==(const QKlipperV412Mode &value);
    bool operator!=(const QKlipperV412Mode &value);

    QString description() const;
    QString format() const;

    QStringList flags() const;
    QStringList resolutions() const;

    void setDescription(const QString &description);
    void setFormat(const QString &format);
    void setFlags(const QStringList &flags);
    void setResolutions(const QStringList &resolutions);

private:
    QString m_description;
    QString m_format;

    QStringList m_flags;
    QStringList m_resolutions;
};

#endif // QKLIPPERV412MODE_H
