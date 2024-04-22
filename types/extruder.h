#ifndef EXTRUDER_H
#define EXTRUDER_H

#include <QObject>
#include "position.h"
#include "fan.h"

class Extruder
{
    Q_GADGET
public:
    Extruder(Position offset = Position());

    void setOffset(Position offset);
    void setOffset(qreal x, qreal y, qreal z);
    Position offset();

    Fan *fan();

    void setCurrentTemp(qreal temp);
    qreal currentTemp();

    void setTargetTemp(qreal temp);
    qreal targetTemp();

    void setPower(qreal power);
    qreal power();

    void setPressureAdvance(qreal advance);
    qreal pressureAdvance();

    void setSmoothTime(qreal time);
    qreal smoothTime();

    void setCanExtrude(bool canExtrude);
    bool canExtrude();

    qreal watts() const;
    void setWatts(qreal watts);

private:
    Position _offset;
    Fan *_fan;
    qreal _currentTemp = 0;
    qreal _targetTemp = 0;
    qreal _smoothTime = 0;
    qreal _pressureAdvance = 0;
    qreal _power = 0;
    qreal _watts = 0;
    bool _canExtrude = false;
};

#endif // EXTRUDER_H
