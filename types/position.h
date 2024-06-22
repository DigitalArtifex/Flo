#ifndef POSITION_H
#define POSITION_H

#include <QObject>
#include <QString>
#include <QMap>

class Position
{
    Q_GADGET
    qreal m_x;
    qreal m_y;
    qreal m_z;
    qreal m_e;

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

//Changing to new position class
class Q3DPrinterPostion
{
    Q_GADGET
    QMap<QString, qreal> m_axisPosition;
public:
    Q3DPrinterPostion() { }

    qreal& operator[](QString key)
    {
        return m_axisPosition[key];
    }
};

typedef Q3DPrinterPostion QGCodePosition;
#endif // POSITION_H
