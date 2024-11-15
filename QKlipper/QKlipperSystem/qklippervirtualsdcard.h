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

#ifndef QKLIPPERVIRTUALSDCARD_H
#define QKLIPPERVIRTUALSDCARD_H

#include <QObject>

class QKlipperSystem;
class QKlipperConsole;

class QKlipperVirtualSDCard : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    explicit QKlipperVirtualSDCard(QObject *parent = nullptr);

    QString filePath() const;

    qint64 fileSize() const;

    qint64 filePosition() const;

    bool isActive() const;

    qreal progress() const;

private slots:
    void setFilePath(const QString &filePath);
    void resetFilePath();

    void setFileSize(qint64 fileSize);
    void resetFileSize();

    void setFilePosition(qint64 filePosition);
    void resetFilePosition();

    void setIsActive(bool isActive);
    void resetIsActive();

    void setProgress(qreal progress);
    void resetProgress();

signals:

    void filePathChanged();

    void fileSizeChanged();

    void filePositionChanged();

    void isActiveChanged();

    void progressChanged();

private:
    QString m_filePath;

    qint64 m_fileSize;
    qint64 m_filePosition;

    bool m_isActive = false;

    qreal m_progress = 0;
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath RESET resetFilePath NOTIFY filePathChanged FINAL)
    Q_PROPERTY(qint64 fileSize READ fileSize WRITE setFileSize RESET resetFileSize NOTIFY fileSizeChanged FINAL)
    Q_PROPERTY(qint64 filePosition READ filePosition WRITE setFilePosition RESET resetFilePosition NOTIFY filePositionChanged FINAL)
    Q_PROPERTY(bool isActive READ isActive WRITE setIsActive RESET resetIsActive NOTIFY isActiveChanged FINAL)
    Q_PROPERTY(qreal progress READ progress WRITE setProgress RESET resetProgress NOTIFY progressChanged FINAL)
};

#endif // QKLIPPERVIRTUALSDCARD_H
