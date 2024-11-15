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

#ifndef QKLIPPERUPDATECOMMIT_H
#define QKLIPPERUPDATECOMMIT_H

#include <QVariant>

class QKlipperUpdateCommit : public QVariant
{
public:
    explicit QKlipperUpdateCommit();

    QKlipperUpdateCommit(const QKlipperUpdateCommit &value);
    QKlipperUpdateCommit &operator=(const QKlipperUpdateCommit &value);
    bool operator==(const QKlipperUpdateCommit &value);
    bool operator!=(const QKlipperUpdateCommit &value);

    QString sha() const;

    QString author() const;

    QString date() const;

    QString subject() const;

    QString message() const;

    QString tag() const;

    void setSha(const QString &sha);

    void setAuthor(const QString &author);

    void setDate(const QString &date);

    void setSubject(const QString &subject);

    void setMessage(const QString &message);

    void setTag(const QString &tag);

private:
    QString m_sha;
    QString m_author;
    QString m_date;
    QString m_subject;
    QString m_message;
    QString m_tag;
};

#endif // QKLIPPERUPDATECOMMIT_H
