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
class QKlipperConsole;

class QKlipperUpdateCommit : public QVariant
{
        friend QKlipperConsole;
    public:
        QKlipperUpdateCommit() = default;

        QKlipperUpdateCommit(const QKlipperUpdateCommit &value)
        {
            m_sha = value.m_sha;
            m_author = value.m_author;
            m_date = value.m_date;
            m_subject = value.m_subject;
            m_message = value.m_message;
            m_tag = value.m_tag;
        }

        ~QKlipperUpdateCommit() = default;

        QKlipperUpdateCommit &operator=(const QKlipperUpdateCommit &value)
        {
            m_sha = value.m_sha;
            m_author = value.m_author;
            m_date = value.m_date;
            m_subject = value.m_subject;
            m_message = value.m_message;
            m_tag = value.m_tag;

            return *this;
        }

        bool operator==(const QKlipperUpdateCommit &value) const
        {
            if(m_sha == value.m_sha  &&
                m_author == value.m_author  &&
                m_date == value.m_date  &&
                m_subject == value.m_subject  &&
                m_message == value.m_message  &&
                m_tag == value.m_tag)
                return true;

            return false;
        }

        bool operator!=(const QKlipperUpdateCommit &value) const { return !(*this == value); }

        const QString sha() const { return m_sha; }

        const QString author() const { return m_author; }

        const QString date() const { return m_date; }

        const QString subject() const { return m_subject; }

        const QString message() const { return m_message; }

        const QString tag() const { return m_tag; }

    protected:
        void setSha(const QString &sha) { m_sha = sha; }

        void setAuthor(const QString &author) { m_author = author; }

        void setDate(const QString &date) { m_date = date; }

        void setSubject(const QString &subject) { m_subject = subject; }

        void setMessage(const QString &message) { m_message = message; }

        void setTag(const QString &tag) { m_tag = tag; }

    private:
        QString m_sha;
        QString m_author;
        QString m_date;
        QString m_subject;
        QString m_message;
        QString m_tag;
};

Q_DECLARE_METATYPE(QKlipperUpdateCommit)
#endif // QKLIPPERUPDATECOMMIT_H
