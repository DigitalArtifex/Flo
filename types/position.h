#ifndef POSITION_H
#define POSITION_H

#include <QObject>

class Position
{
    Q_GADGET
    qreal _x;
    qreal _y;
    qreal _z;

public:
    Position();
    Position(qreal x, qreal y, qreal z);

    void set(qreal x, qreal y, qreal z);

    void setX(qreal x);
    qreal x();

    void setY(qreal y);
    qreal y();

    void setZ(qreal z);
    qreal z();
};

#endif // POSITION_H
