#ifndef CHAMBER_H
#define CHAMBER_H

#include <QObject>

class Chamber : public QObject
{
    Q_OBJECT
public:
    Chamber();

    qreal watts() const;
    void setWatts(qreal watts);

private:
    qreal m_watts = 0;
};

#endif // CHAMBER_H
