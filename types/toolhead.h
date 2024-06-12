#ifndef TOOLHEAD_H
#define TOOLHEAD_H

#include <QObject>
#include <QMap>

#include "extruder.h"
#include "position.h"

class Printer;

class Toolhead : public QObject
{
    Q_OBJECT

    friend class QAbstractKlipperConsole;
    friend class Printer;
public:
    Toolhead(Printer *printer, QObject *parent = nullptr);

    void addExtruder(Extruder *extruder);
    Fan *fan();
    Position position();
    Position destination();

    void setPosition(Position position);
    void setPosition(qreal x, qreal y, qreal z);

    Position maxPosition();
    Position minPosition();

    /*!
     * \brief Home X Axis
     */
    void homeX();

    /*!
     * \brief Home Y Axis
     */
    void homeY();

    /*!
     * \brief Home Z Axis
     */
    void homeZ();

    bool isZHomed();
    bool isYHomed();
    bool isXHomed();
    bool isHomed();

    /*!
     * \brief Moves the X axis
     *
     * Moves the axis by the specified amount. If speed is 0 the default speed in klipper is used
     *
     * \param amount
     * \param speed
     */
    void moveX(qreal amount, qreal speed = 0);

    /*!
     * \brief Moves the Y axis
     *
     * Moves the axis by the specified amount. If speed is 0 the default speed in klipper is used
     *
     * \param amount
     * \param speed
     */
    void moveY(qreal amount, qreal speed = 0);

    /*!
     * \brief Moves the Z axis
     *
     * Moves the axis by the specified amount. If speed is 0 the default speed in klipper is used
     *
     * \param amount
     * \param speed
     */
    void moveZ(qreal amount, qreal speed = 0);

    void homeAll();

    int extruderCount();
    Extruder *currentExtruder();
    Extruder *extruderByName(QString name);
    Extruder *extruder(int index);

    QString homedAxes();

    qint32 maxAcceleration() const;
    void setMaxAcceleration(qint32 maxAcceleration);

    qint32 maxVelocity() const;
    void setMaxVelocity(qint32 maxVelocity);

    qint32 maxAccelerationToDeceleration() const;
    void setMaxAccelerationToDeceleration(qint32 maxAccelerationToDeceleration);

    qint32 stalls() const;

    Printer *printer() const;
    void setPrinter(Printer *printer);

    void setExtruderMaxWatts(qint32 extruder, qreal watts);

signals:
    void homing();
    void homed();
    void updated();

private:
    void update();

    Position _position;
    Position _destination;
    Position _maxPosition;
    Position _minPosition;
    Fan *_fan;
    QMap<int, Extruder*> _extruders;
    QString _currentExtruderName;

    bool _zHomed = false;
    bool _yHomed = false;
    bool _xHomed = false;
    bool _isHoming = false;
    bool _isXHoming = false;
    bool _isYHoming = false;
    bool _isZHoming = false;

    qint32 _maxAcceleration = 0;
    qint32 _maxVelocity = 0;
    qint32 _maxAccelerationToDeceleration = 0;
    qint32 _stalls = 0;
    qint32 _checks = 0;

    qreal _squareCornerVelocity = 0;

    Printer *_printer = nullptr;
};

#endif // TOOLHEAD_H
