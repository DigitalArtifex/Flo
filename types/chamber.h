#ifndef CHAMBER_H
#define CHAMBER_H

#include <QObject>

class Chamber : public QObject
{
    Q_OBJECT
public:
    Chamber();

    qreal watts() const;

    qreal maxWatts() const;
    void setMaxWatts(qreal maxWatts);

    qreal power() const;
    void setPower(qreal power);

signals:
    void updated(Chamber*);

private:
    qreal m_watts = 0;
    qreal m_maxWatts = 0;
    qreal m_power = 0;
};

#endif // CHAMBER_H
