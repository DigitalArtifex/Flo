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

#ifndef QKLIPPERFILE_H
#define QKLIPPERFILE_H

#include <QObject>
#include <QString>
#include <QDir>

#include "qklippermetadata.h"

class QKlipperFile : public QObject
{
    Q_OBJECT
public:
    enum FileType {
        GCode,
        GCodeMacro,
        Config,
        Directory
    };

    explicit QKlipperFile(QObject *parent = nullptr);

    QString root() const;

    QString filename() const;

    QString uri() const;

    FileType fileType() const;

    QKlipperMetadata metadata() const;

    QString path() const;

    QString uuid() const;

    qint64 fileSize() const;

    qreal dateModified() const;

public slots:
    void setRoot(const QString &root);
    void resetRoot();

    void setFilename(const QString &filename);
    void resetFilename();

    void setFileType(FileType fileType);
    void resetFileType();

    void setMetadata(const QKlipperMetadata &metadata);
    void resetMetadata();

    void setPath(const QString &path);
    void resetPath();

    void setUuid(const QString &uuid);

    void setFileSize(qint64 fileSize);

    void setDateModified(qreal dateModified);

signals:

    void rootChanged();
    void currentDirectoryChanged();
    void filenameChanged();
    void fileTypeChanged();
    void metadataChanged();

    void pathChanged();

    void uuidChanged();

    void fileSizeChanged();

    void dateModifiedChanged();

private:
    QString m_root;
    QString m_path;
    QString m_filename;
    QString m_uri;
    QString m_uuid;

    qint64 m_fileSize = 0;
    qreal m_dateModified = 0;

    FileType m_fileType = GCode;
    QKlipperMetadata m_metadata;

    Q_PROPERTY(QString root READ root WRITE setRoot RESET resetRoot NOTIFY rootChanged FINAL)
    Q_PROPERTY(QString filename READ filename WRITE setFilename RESET resetFilename NOTIFY filenameChanged FINAL)
    Q_PROPERTY(FileType fileType READ fileType WRITE setFileType RESET resetFileType NOTIFY fileTypeChanged FINAL)
    Q_PROPERTY(QKlipperMetadata metadata READ metadata WRITE setMetadata RESET resetMetadata NOTIFY metadataChanged FINAL)
    Q_PROPERTY(QString uri READ uri CONSTANT FINAL)
    Q_PROPERTY(QString path READ path WRITE setPath RESET resetPath NOTIFY pathChanged FINAL)
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid NOTIFY uuidChanged FINAL)
    Q_PROPERTY(qint64 fileSize READ fileSize WRITE setFileSize NOTIFY fileSizeChanged FINAL)
    Q_PROPERTY(qreal dateModified READ dateModified WRITE setDateModified NOTIFY dateModifiedChanged FINAL)
};

typedef QList<QKlipperFile*> QKlipperFileList;

#endif // QKLIPPERFILE_H
