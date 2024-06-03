#ifndef EXTRUDER_H
#define EXTRUDER_H

#include <QObject>
#include "position.h"
#include "fan.h"
#include "temperaturestore.h"

class Printer;

class Extruder : public QObject
{
    Q_OBJECT
    friend class QAbstractKlipperConsole;
    friend class Printer;
    friend class Toolhead;

public:
    Extruder(Printer *printer, Position offset = Position(), QObject *parent = nullptr);

    void setOffset(Position offset);
    void setOffset(qreal x, qreal y, qreal z);
    Position offset();

    Fan *fan();

    qreal currentTemp();

    void setTargetTemp(qreal temp);
    qreal targetTemp();
    qreal power();

    void setPressureAdvance(qreal advance, qreal smoothTime);
    qreal pressureAdvance();
    qreal smoothTime();

    bool canExtrude();

    void extrude(qreal amount, qreal speed);
    void retract(qreal amount, qreal speed);

    qreal watts() const;

    TemperatureStore temperatureStore() const;

    Printer *printer() const;
    void setPrinter(Printer *printer);

    qreal extrusionFactor() const;
    void setExtrusionFactor(qreal extrusionFactor);

    QString name() const;

    QPair<qint32, qint32> gearRatio() const;

    qint32 extruderNumber() const;
    qint32 fullStepsPerRotation() const;
    qint32 microsteps() const;

    qreal pressureAdvanceSmoothTime() const;
    qreal filamentDiameter() const;
    qreal nozzleDiameter() const;
    qreal inlineResistor() const;
    qreal pullupResistor() const;

    qreal pwmCycle() const;
    qreal rotationDistance() const;
    qreal instantCornerVelocity() const;

    qreal pidKD() const;
    qreal pidKI() const;
    qreal pidKP() const;

    qreal maxExtrudeCrossSection() const;
    qreal maxExtrudeOnlyAcceleration() const;
    qreal maxExtrudeOnlyDistance() const;
    qreal maxExtrudeOnlyVelocity() const;
    qreal maxTemp() const;
    qreal maxPower() const;

    QString control() const;
    QString dirPin() const;
    QString enablePin() const;
    QString heaterPin() const;
    QString sensorPin() const;
    QString sensorType() const;
    QString stepPin() const;

    qreal minExtrudeTemp() const;

    qreal minTemp() const;

signals:
    void updated(Extruder *extruder);

protected:
    void emitUpdate();

private:
    Position _offset;
    Fan *_fan;

    QPair<qint32,qint32> _gearRatio;

    qint32 _extruderNumber = 0;
    qint32 _fullStepsPerRotation = 0;
    qint32 _microsteps = 0;

    qreal _currentTemp = 0;
    qreal _targetTemp = 0;
    qreal _smoothTime = 0;
    qreal _pressureAdvance = 0;
    qreal _pressureAdvanceSmoothTime = 0;
    qreal _extrusionFactor = 0;
    qreal _filamentDiameter = 0;
    qreal _nozzleDiameter = 0;
    qreal _power = 0;
    qreal _watts = 0;
    qreal _inlineResistor = 0;
    qreal _pullupResistor = 0;
    qreal _pwmCycle = 0;
    qreal _rotationDistance = 0;
    qreal _instantCornerVelocity = 0;

    //pid settings
    qreal _pidKD = 0;
    qreal _pidKI = 0;
    qreal _pidKP = 0;

    //maximums
    qreal _maxExtrudeCrossSection = 0;
    qreal _maxExtrudeOnlyAcceleration = 0;
    qreal _maxExtrudeOnlyDistance = 0;
    qreal _maxExtrudeOnlyVelocity = 0;
    qreal _maxTemp = 0;
    qreal _maxPower = 0;

    //minimums
    qreal _minExtrudeTemp = 0;
    qreal _minTemp = 0;

    bool _canExtrude = false;

    QString _name;
    QString _control;
    QString _dirPin;
    QString _enablePin;
    QString _heaterPin;
    QString _sensorPin;
    QString _sensorType;
    QString _stepPin;

    TemperatureStore _temperatureStore;

    //Parent printer object
    Printer *_printer = nullptr;
};

#endif // EXTRUDER_H
