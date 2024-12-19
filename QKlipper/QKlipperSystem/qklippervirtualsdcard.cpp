#include "qklippervirtualsdcard.h"

QKlipperVirtualSDCard::QKlipperVirtualSDCard(QObject *parent)
    : QObject{parent}
{}

QString QKlipperVirtualSDCard::filePath() const
{
    return m_filePath;
}

void QKlipperVirtualSDCard::setFilePath(const QString &filePath)
{
    if (m_filePath == filePath)
        return;
    m_filePath = filePath;
    emit filePathChanged();
}

void QKlipperVirtualSDCard::resetFilePath()
{
    setFilePath({}); // TODO: Adapt to use your actual default value
}

qint64 QKlipperVirtualSDCard::fileSize() const
{
    return m_fileSize;
}

void QKlipperVirtualSDCard::setFileSize(qint64 fileSize)
{
    if (m_fileSize == fileSize)
        return;
    m_fileSize = fileSize;
    emit fileSizeChanged();
}

void QKlipperVirtualSDCard::resetFileSize()
{
    setFileSize({}); // TODO: Adapt to use your actual default value
}

qint64 QKlipperVirtualSDCard::filePosition() const
{
    return m_filePosition;
}

void QKlipperVirtualSDCard::setFilePosition(qint64 filePosition)
{
    if (m_filePosition == filePosition)
        return;
    m_filePosition = filePosition;
    emit filePositionChanged();
}

void QKlipperVirtualSDCard::resetFilePosition()
{
    setFilePosition({}); // TODO: Adapt to use your actual default value
}

bool QKlipperVirtualSDCard::isActive() const
{
    return m_isActive;
}

void QKlipperVirtualSDCard::setIsActive(bool isActive)
{
    if (m_isActive == isActive)
        return;
    m_isActive = isActive;
    emit isActiveChanged();
}

void QKlipperVirtualSDCard::resetIsActive()
{
    setIsActive({}); // TODO: Adapt to use your actual default value
}

qreal QKlipperVirtualSDCard::progress() const
{
    return m_progress;
}

void QKlipperVirtualSDCard::setValue(qreal progress)
{
    if (qFuzzyCompare(m_progress, progress))
        return;
    m_progress = progress;
    emit progressChanged();
}

void QKlipperVirtualSDCard::resetValue()
{
    setValue({}); // TODO: Adapt to use your actual default value
}
