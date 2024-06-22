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
    Position m_offset;
    Fan *m_fan;

    QPair<qint32,qint32> m_gearRatio;

    qint32 m_extruderNumber = 0;
    qint32 m_fullStepsPerRotation = 0;
    qint32 m_microsteps = 0;

    qreal m_currentTemp = 0;
    qreal m_targetTemp = 0;
    qreal m_smoothTime = 0;
    qreal m_pressureAdvance = 0;
    qreal m_pressureAdvanceSmoothTime = 0;
    qreal m_extrusionFactor = 0;
    qreal m_filamentDiameter = 0;
    qreal m_nozzleDiameter = 0;
    qreal m_power = 0;
    qreal m_watts = 0;
    qreal m_inlineResistor = 0;
    qreal m_pullupResistor = 0;
    qreal m_pwmCycle = 0;
    qreal m_rotationDistance = 0;
    qreal m_instantCornerVelocity = 0;

    //pid settings
    qreal m_pidKD = 0;
    qreal m_pidKI = 0;
    qreal m_pidKP = 0;

    //maximums
    qreal m_maxExtrudeCrossSection = 0;
    qreal m_maxExtrudeOnlyAcceleration = 0;
    qreal m_maxExtrudeOnlyDistance = 0;
    qreal m_maxExtrudeOnlyVelocity = 0;
    qreal m_maxTemp = 0;
    qreal m_maxPower = 0;

    //minimums
    qreal m_minExtrudeTemp = 0;
    qreal m_minTemp = 0;

    bool m_canExtrude = false;

    QString m_name;
    QString m_control;
    QString m_dirPin;
    QString m_enablePin;
    QString m_heaterPin;
    QString m_sensorPin;
    QString m_sensorType;
    QString m_stepPin;

    TemperatureStore m_temperatureStore;

    //Parent printer object
    Printer *m_printer = nullptr;
};

#endif // EXTRUDER_H
