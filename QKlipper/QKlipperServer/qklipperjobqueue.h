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

#ifndef QKLIPPERJOBQUEUE_H
#define QKLIPPERJOBQUEUE_H

#include <QObject>

#include "qklipperprintjob.h"

class QKlipperSystem;
class QKlipperConsole;

class QKlipperJobQueue : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    enum State
    {
        Ready,
        Paused,
        Loading,
        Starting,
        Error
    };

    explicit QKlipperJobQueue(QObject *parent = nullptr);


    QList<QKlipperPrintJob *> queue() const;

    State state() const;
    QKlipperPrintJob *job(QString id);

public slots:

    void setQueue(const QList<QKlipperPrintJob*> &queue);
    void addJob(QKlipperPrintJob *job);
    void removeJob(QKlipperPrintJob* job);
    void removeJob(const QString &jobId);
    void clearJobs();

    void setState(State state);

private slots:

signals:
    void queueChanged();
    void stateChanged();
    void jobAdded(QKlipperPrintJob *);
    void jobRemoved(QKlipperPrintJob *);

private:
    QList<QKlipperPrintJob*> m_queue;
    State m_state = Error;

    Q_PROPERTY(QList<QKlipperPrintJob*> queue READ queue WRITE setQueue NOTIFY queueChanged FINAL)
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged FINAL)
};

#endif // QKLIPPERJOBQUEUE_H
