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

    long timeRunning();
    qreal currentTemp() const;
    void setCurrentTemp(qreal currentTemp);

    qreal targetTemp() const;
    void setTargetTemp(qreal targetTemp);

    qreal power() const;
    void setPower(qreal power);

    qreal watts() const;
    void setWatts(qreal watts);

private:
    qreal _currentTemp = 0;
    qreal _targetTemp = 0;
    qreal _power = 0;
    qreal _watts = 0;

    QDateTime _startTime;
};

#endif // BED_H
