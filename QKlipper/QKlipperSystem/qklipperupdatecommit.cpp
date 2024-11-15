#include "qklipperupdatecommit.h"

QKlipperUpdateCommit::QKlipperUpdateCommit()
    : QVariant{}
{}

QKlipperUpdateCommit::QKlipperUpdateCommit(const QKlipperUpdateCommit &value)
{
    m_sha = value.m_sha;
    m_author = value.m_author;
    m_date = value.m_date;
    m_subject = value.m_subject;
    m_message = value.m_message;
    m_tag = value.m_tag;
}

QKlipperUpdateCommit &QKlipperUpdateCommit::operator=(const QKlipperUpdateCommit &value)
{
    m_sha = value.m_sha;
    m_author = value.m_author;
    m_date = value.m_date;
    m_subject = value.m_subject;
    m_message = value.m_message;
    m_tag = value.m_tag;

    return *this;
}

bool QKlipperUpdateCommit::operator==(const QKlipperUpdateCommit &value)
{
    if(m_sha != value.m_sha) return false;
    if(m_author != value.m_author) return false;
    if(m_date != value.m_date) return false;
    if(m_subject != value.m_subject) return false;
    if(m_message != value.m_message) return false;
    if(m_tag != value.m_tag) return false;

    return true;
}

bool QKlipperUpdateCommit::operator!=(const QKlipperUpdateCommit &value)
{
    if(m_sha == value.m_sha &&
        m_author == value.m_author &&
        m_date == value.m_date &&
        m_subject == value.m_subject &&
        m_message == value.m_message &&
        m_tag == value.m_tag) return false;

    return true;
}

QString QKlipperUpdateCommit::sha() const
{
    return m_sha;
}

void QKlipperUpdateCommit::setSha(const QString &sha)
{
    m_sha = sha;
}

QString QKlipperUpdateCommit::author() const
{
    return m_author;
}

void QKlipperUpdateCommit::setAuthor(const QString &author)
{
    m_author = author;
}

QString QKlipperUpdateCommit::date() const
{
    return m_date;
}

void QKlipperUpdateCommit::setDate(const QString &date)
{
    m_date = date;
}

QString QKlipperUpdateCommit::subject() const
{
    return m_subject;
}

void QKlipperUpdateCommit::setSubject(const QString &subject)
{
    m_subject = subject;
}

QString QKlipperUpdateCommit::message() const
{
    return m_message;
}

void QKlipperUpdateCommit::setMessage(const QString &message)
{
    m_message = message;
}

QString QKlipperUpdateCommit::tag() const
{
    return m_tag;
}

void QKlipperUpdateCommit::setTag(const QString &tag)
{
    m_tag = tag;
}
