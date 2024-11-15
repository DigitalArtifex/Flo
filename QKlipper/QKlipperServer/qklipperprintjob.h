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

#ifndef QKLIPPERPRINTJOB_H
#define QKLIPPERPRINTJOB_H

#include <QObject>
#include <QVariant>

class QKlipperPrintJob : public QObject
{
    Q_OBJECT
public:

    enum State {
        Standby,
        Printing,
        Paused,
        Complete,
        Cancelled,
        Error
    };

    explicit QKlipperPrintJob(QObject *parent = nullptr);

    QString filename() const;
    void setFilename(const QString &filename);

    QString id() const;
    void setId(const QString &id);

    qreal timeAdded() const;
    void setTimeAdded(qreal timeAdded);

    qreal timeInQueue() const;
    void setTimeInQueue(qreal timeInQueue);

    State state() const;

    QString message() const;

    qreal totalDuration() const;

    qreal printDuration() const;

    qreal filamentUsed() const;

    qint64 totalLayers() const;

    qint64 currentLayer() const;

    qreal progress() const;

public slots:
    void setState(State state);

    void setState(QString state);

    void setMessage(const QString &message);

    void setTotalDuration(qreal totalDuration);

    void setPrintDuration(qreal printDuration);

    void setFilamentUsed(qreal filamentUsed);

    void setTotalLayers(qint64 totalLayers);

    void setCurrentLayer(qint64 currentLayer);

signals:

    void filenameChanged();

    void idChanged();

    void timeAddedChanged();

    void timeInQueueChanged();

    void stateChanged();

    void messageChanged();

    void totalDurationChanged();

    void printDurationChanged();

    void filamentUsedChanged();

    void totalLayersChanged();

    void currentLayerChanged();

    void started(QKlipperPrintJob *job);
    void finished(QKlipperPrintJob *job);
    void cancelled(QKlipperPrintJob *job);
    void error(QKlipperPrintJob *job);
    void paused(QKlipperPrintJob *job);
    void resumed(QKlipperPrintJob *job);
    void standby(QKlipperPrintJob *job);

private:
    QString m_filename;
    QString m_id;

    qreal m_timeAdded;
    qreal m_timeInQueue;

    State m_state = Error;

    QString m_message;

    qreal m_totalDuration = 0.0;
    qreal m_printDuration = 0.0;
    qreal m_filamentUsed = 0.0;

    qint64 m_totalLayers = 0;
    qint64 m_currentLayer = 0;

    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged FINAL)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(qreal timeAdded READ timeAdded WRITE setTimeAdded NOTIFY timeAddedChanged FINAL)
    Q_PROPERTY(qreal timeInQueue READ timeInQueue WRITE setTimeInQueue NOTIFY timeInQueueChanged FINAL)
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged FINAL)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged FINAL)
    Q_PROPERTY(qreal totalDuration READ totalDuration WRITE setTotalDuration NOTIFY totalDurationChanged FINAL)
    Q_PROPERTY(qreal printDuration READ printDuration WRITE setPrintDuration NOTIFY printDurationChanged FINAL)
    Q_PROPERTY(qreal filamentUsed READ filamentUsed WRITE setFilamentUsed NOTIFY filamentUsedChanged FINAL)
    Q_PROPERTY(qint64 totalLayers READ totalLayers WRITE setTotalLayers NOTIFY totalLayersChanged FINAL)
    Q_PROPERTY(qint64 currentLayer READ currentLayer WRITE setCurrentLayer NOTIFY currentLayerChanged FINAL)
};

#endif // QKLIPPERPRINTJOB_H
