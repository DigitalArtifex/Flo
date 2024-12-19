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

#ifndef QKLIPPERANNOUNCEMENT_H
#define QKLIPPERANNOUNCEMENT_H

#include <QVariant>

class QKlipperSystem;
class QKlipperConsole;

class QKlipperAnnouncement
{
    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    QKlipperAnnouncement() = default;
    QKlipperAnnouncement(const QKlipperAnnouncement &value)
    {
        m_entryId = value.entryId();
        m_date = value.date();
        m_dateDismissed = value.dateDismissed();
        m_isDismissed = value.isDismissed();
        m_description = value.description();
        m_feed = value.feed();
        m_priority = value.priority();
        m_source = value.source();
        m_title = value.title();
        m_url = value.url();
    }

    ~QKlipperAnnouncement() = default;

    QKlipperAnnouncement &operator=(const QKlipperAnnouncement &value)
    {
        m_entryId = value.entryId();
        m_date = value.date();
        m_dateDismissed = value.dateDismissed();
        m_isDismissed = value.isDismissed();
        m_description = value.description();
        m_feed = value.feed();
        m_priority = value.priority();
        m_source = value.source();
        m_title = value.title();
        m_url = value.url();

        return *this;
    }

    bool operator==(const QKlipperAnnouncement &value) const
    {
        if(m_isDismissed == value.m_isDismissed &&
            m_dateDismissed == value.m_dateDismissed &&
            m_dateDismissedWake == value.m_dateDismissedWake &&
            m_date == value.m_date &&
            m_description == value.m_description &&
            m_entryId == value.m_entryId &&
            m_feed == value.m_feed &&
            m_priority == value.m_priority &&
            m_source == value.m_source &&
            m_title == value.m_title &&
            m_url == value.m_url )
            return true;

        return false;
    }

    bool operator!=(const QKlipperAnnouncement &value) const { return !(*this == value); }

    QString entryId() const { return m_entryId; }

    QString url() const { return m_url; }

    QString title() const { return m_title; }

    QString description() const { return m_description; }

    QString priority() const { return m_priority; }

    QString feed() const { return m_feed; }

    QString source() const { return m_source; }

    qreal date() const { return m_date; }

    qreal dateDismissed() const { return m_dateDismissed; }

    qreal dateDismissedWake() const { return m_dateDismissedWake; }

    bool isDismissed() const { return m_isDismissed; }

private:
    void setEntryId(const QString &entryId) { m_entryId = entryId; }
    void setUrl(const QString &url) { m_url = url; }
    void setTitle(const QString &title) { m_title = title; }
    void setDescription(const QString &description) { m_description = description; }
    void setPriority(const QString &priority) { m_priority = priority; }
    void setFeed(const QString &feed) { m_feed = feed; }
    void setSource(const QString &source) { m_source = source; }
    void setDate(qreal date) { m_date = date; }
    void setDateDismissed(qreal dateDismissed) { m_dateDismissed = dateDismissed; }
    void setDateDismissedWake(qreal dateDismissedWake) { m_dateDismissedWake = dateDismissedWake; }
    void setIsDismissed(bool isDismissed) { m_isDismissed = isDismissed; }

    QString m_entryId;
    QString m_url;
    QString m_title;
    QString m_description;
    QString m_priority;
    QString m_feed;
    QString m_source;

    qreal m_date = 0;
    qreal m_dateDismissed = 0;
    qreal m_dateDismissedWake = 0;

    bool m_isDismissed = false;
};

Q_DECLARE_METATYPE(QKlipperAnnouncement)
typedef QList<QKlipperAnnouncement> QKlipperAnnouncementList;

#endif // QKLIPPERANNOUNCEMENT_H
