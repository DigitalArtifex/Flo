#ifndef POSITION_H
#define POSITION_H

#include <QObject>

class Position
{
    Q_GADGET
    qreal _x;
    qreal _y;
    qreal _z;
    qreal _e;

public:
    Position();
    Position(qreal x, qreal y, qreal z, qreal e = 0);

    void set(qreal x, qreal y, qreal z);

    void setX(qreal x);
    qreal x();

    void setY(qreal y);
    qreal y();

    void setZ(qreal z);
    qreal z();

    void setE(qreal e);
    qreal e();
};

#endif // POSITION_H
