#include "qklipperannouncement.h"

QKlipperAnnouncement::QKlipperAnnouncement()
    : QVariant{}
{

}

QKlipperAnnouncement::QKlipperAnnouncement(const QKlipperAnnouncement &value)
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

QKlipperAnnouncement &QKlipperAnnouncement::operator=(const QKlipperAnnouncement &value)
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

QString QKlipperAnnouncement::entryId() const
{
    return m_entryId;
}

void QKlipperAnnouncement::setEntryId(const QString &entryId)
{
    m_entryId = entryId;
}

QString QKlipperAnnouncement::url() const
{
    return m_url;
}

void QKlipperAnnouncement::setUrl(const QString &url)
{
    m_url = url;
}

QString QKlipperAnnouncement::title() const
{
    return m_title;
}

void QKlipperAnnouncement::setTitle(const QString &title)
{
    m_title = title;
}

QString QKlipperAnnouncement::description() const
{
    return m_description;
}

void QKlipperAnnouncement::setDescription(const QString &description)
{
    m_description = description;
}

QString QKlipperAnnouncement::priority() const
{
    return m_priority;
}

void QKlipperAnnouncement::setPriority(const QString &priority)
{
    m_priority = priority;
}

QString QKlipperAnnouncement::feed() const
{
    return m_feed;
}

void QKlipperAnnouncement::setFeed(const QString &feed)
{
    m_feed = feed;
}

QString QKlipperAnnouncement::source() const
{
    return m_source;
}

void QKlipperAnnouncement::setSource(const QString &source)
{
    m_source = source;
}

qreal QKlipperAnnouncement::date() const
{
    return m_date;
}

void QKlipperAnnouncement::setDate(qreal date)
{
    m_date = date;
}

qreal QKlipperAnnouncement::dateDismissed() const
{
    return m_dateDismissed;
}

void QKlipperAnnouncement::setDateDismissed(qreal dateDismissed)
{
    m_dateDismissed = dateDismissed;
}

qreal QKlipperAnnouncement::dateDismissedWake() const
{
    return m_dateDismissedWake;
}

void QKlipperAnnouncement::setDateDismissedWake(qreal dateDismissedWake)
{
    m_dateDismissedWake = dateDismissedWake;
}

bool QKlipperAnnouncement::isDismissed() const
{
    return m_isDismissed;
}

void QKlipperAnnouncement::setIsDismissed(bool isDismissed)
{
    m_isDismissed = isDismissed;
}
