#include "qklipperfile.h"

QKlipperFile::QKlipperFile(QObject *parent)
    : QObject{parent}
{

}

QString QKlipperFile::root() const
{
    return m_root;
}

void QKlipperFile::setRoot(const QString &root)
{
    if (m_root == root)
        return;

    m_root = root;
    emit rootChanged();
}

void QKlipperFile::resetRoot()
{
    setRoot(QString());
}

QString QKlipperFile::filename() const
{
    return m_filename;
}

void QKlipperFile::setFilename(const QString &filename)
{
    if (m_filename == filename)
        return;

    m_filename = filename;
    emit filenameChanged();
}

void QKlipperFile::resetFilename()
{
    setFilename(QString());
}

QKlipperFile::FileType QKlipperFile::fileType() const
{
    return m_fileType;
}

void QKlipperFile::setFileType(FileType fileType)
{
    if (m_fileType == fileType)
        return;

    m_fileType = fileType;
    emit fileTypeChanged();
}

void QKlipperFile::resetFileType()
{
    setFileType(GCode);
}

QKlipperMetadata QKlipperFile::metadata() const
{
    return m_metadata;
}

void QKlipperFile::setMetadata(const QKlipperMetadata &metadata)
{
    m_metadata = metadata;
    emit metadataChanged();
}

void QKlipperFile::resetMetadata()
{
    setMetadata(QKlipperMetadata());
}

QString QKlipperFile::path() const
{
    return m_path;
}

void QKlipperFile::setPath(const QString &path)
{
    if (m_path == path)
        return;

    m_path = path;
    emit pathChanged();
}

void QKlipperFile::resetPath()
{
    setPath({}); // TODO: Adapt to use your actual default value
}

QString QKlipperFile::uuid() const
{
    return m_uuid;
}

void QKlipperFile::setUuid(const QString &uuid)
{
    if (m_uuid == uuid)
        return;
    m_uuid = uuid;
    emit uuidChanged();
}

qint64 QKlipperFile::fileSize() const
{
    return m_fileSize;
}

void QKlipperFile::setFileSize(qint64 fileSize)
{
    if (m_fileSize == fileSize)
        return;

    m_fileSize = fileSize;
    emit fileSizeChanged();
}

qreal QKlipperFile::dateModified() const
{
    return m_dateModified;
}

void QKlipperFile::setDateModified(qreal dateModified)
{
    if (qFuzzyCompare(m_dateModified, dateModified))
        return;

    m_dateModified = dateModified;
    emit dateModifiedChanged();
}

QString QKlipperFile::uri() const
{
    QString uri;
    QString root = m_root;
    QString path = m_path;

    if(root.endsWith("/"))
        root.removeLast();

    if(path.endsWith("/"))
        path.removeLast();

    if(!m_path.isEmpty())
        uri = QString("%1/%2/%3").arg(root, path, m_filename);
    else
        uri = QString("%1/%2").arg(root, m_filename);

    return uri;
}
