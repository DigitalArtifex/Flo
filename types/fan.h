#ifndef FAN_H
#define FAN_H

#include <QObject>

class Fan
{
    Q_GADGET
public:
    Fan();

    void setSpeed(qreal speed);
    qreal speed();

    void setRpm(qreal rpm);
    qreal rpm();

private:
    qreal _speed;
    qreal _rpm;
};

#endif // FAN_H
