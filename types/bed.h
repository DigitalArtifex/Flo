#ifndef BED_H
#define BED_H

#include <QObject>
#include <QDateTime>

class Bed
{
    Q_GADGET
public:
    enum Type
    {
        Heated,
        NonHeated
    };

    Bed(Type type = NonHeated);

    void setCurrentTemp(qreal temp);
    qreal currentTemp();

    void setTargetTemp(qreal temp);
    qreal targetTemp();

    void setPower(qreal power);
    qreal power();

    void setStartTime(QDateTime time);

    long timeRunning();
private:
    qreal _currentTemp;
    qreal _targetTemp;
    qreal _timeRunning;
    qreal _power;
    QDateTime _startTime;
};

#endif // BED_H
