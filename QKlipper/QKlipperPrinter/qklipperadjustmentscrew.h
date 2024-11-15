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

#ifndef QKLIPPERADJUSTMENTSCREW_H
#define QKLIPPERADJUSTMENTSCREW_H

#include <QObject>

class QKlipperAdjustmentScrew : public QObject
{
    Q_OBJECT
public:
    struct Adjustment
    {
        enum Direction
        {
            Clockwise,
            CounterClockwise,
            NotSet = -1
        };

        //Ratio string
        QString amount;
        QString sign;

        Direction direction = NotSet;

        bool isBase = false;

        qreal z = 0;
    };

    explicit QKlipperAdjustmentScrew(QObject *parent = nullptr);

    QString name() const;

    QString thread() const;

    QPair<qreal, qreal> tiltAdjust() const;

    qreal speed() const;

    Adjustment adjustment() const;

public slots:
    void setName(const QString &name);
    void setThread(const QString &thread);
    void setTiltAdjust(const QPair<qreal, qreal> &tiltAdjust);
    void setSpeed(qreal speed);
    void setAdjustment(const Adjustment &adjustment);

signals:
    void nameChanged();
    void threadChanged();
    void tiltAdjustChanged();
    void speedChanged();
    void adjustmentChanged();

private:
    QString m_name;
    QString m_thread;

    QPair<qreal,qreal> m_tiltAdjust;

    qreal m_speed;

    Adjustment m_adjustment;

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString thread READ thread WRITE setThread NOTIFY threadChanged FINAL)
    Q_PROPERTY(QPair<qreal, qreal> tiltAdjust READ tiltAdjust WRITE setTiltAdjust NOTIFY tiltAdjustChanged FINAL)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(Adjustment adjustment READ adjustment WRITE setAdjustment NOTIFY adjustmentChanged FINAL)
};

//Q_DECLARE_METATYPE(QKlipperAdjustmentScrew::Adjustment)

#endif // QKLIPPERADJUSTMENTSCREW_H
