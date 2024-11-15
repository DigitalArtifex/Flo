/*!
 * QKlipper - A Qt library for the Klipper/Moonraker API
 * Copyright (C) 2024 James Dudeck
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QKLIPPERFAN_H
#define QKLIPPERFAN_H

#include <QObject>

class QKlipperPrinter;
class QKlipperConsole;

//!  QKlipperFan class
/*!
  This class is responsible for monitoring and controlling fan objects.

  Not all fans are controllable.
*/
class QKlipperFan : public QObject
{
    Q_OBJECT

    friend QKlipperConsole;
    friend QKlipperPrinter;
public:
    //!  State enum
    /*!
      This enum provides flags for the on/off states
    */
    enum State
    {
        Off = 0, /*!!< Fan is off */
        On = 1 /*!!< Fan is on */
    };

    /*!
     * Constructor
     *
     * \param parent The parent object
     */
    explicit QKlipperFan(QObject *parent = nullptr);

    /*!
     * Name of the fan object
     *
     * \returns The current name of the fan
     */
    QString name() const;

    /*!
     * Current speed of the fan
     *
     * \returns The current speed of the fan
     */
    qreal speed() const;

    /*!
     * Current RPM
     *
     * \returns The current RPM of the fan (if available)
     */
    qreal rpm() const;

    /*!
     * Controllable state of the fan object
     *
     * \returns True if the fan can be controlled
     */
    bool isControllable() const;

    /*!
     * Current console object
     *
     * \returns The current console object
     */
    QKlipperConsole *console() const;

public slots:
    /*!
     * Sends a gcode script to set the requested speed
     *
     * \param speed The value to set (0-100)
     */
    void setSpeed(qreal speed);


private slots:
    /*!
     * Sets the name value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     *
     * \param name Name of the fan object
     */
    void setNameData(const QString &name);

    /*!
     * Resets the name value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     */
    void resetName();

    /*!
     * Sets the speed value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     *
     * \param speed Speed of the fan object
     */
    void setSpeedData(qreal speed);

    /*!
     * Resets the speed value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     */
    void resetSpeed();

    /*!
     * Sets the rpm value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     *
     * \param rpm RPM of the fan object
     */
    void setRpmData(qreal rpm);

    /*!
     * Resets the rpm value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     */
    void resetRpm();

    /*!
     * Sets the controllable value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     *
     * \param isControllable State of controllability
     */
    void setIsControllable(bool isControllable);

    /*!
     * Resets the controllable value of the fan object ONLY. It does not
     * send any klipper commands. Primarily used by QKlipperConsole
     */
    void resetIsControllable();

    /*!
     * Sets the console object of the fan. This is used to send commands
     * for the fan to klipper
     *
     * \param console Console of the current object
     */
    void setConsole(QKlipperConsole *console);

signals:

    //Signal fired when setNameData has been called with new data
    void nameChanged();

    //Signal fired when setSpeedData has been called with new data
    void speedChanged();

    //Signal fired when setRpmData has been called with new data
    void rpmChanged();

    //Signal fired when setIsControllableData has been called with new data
    void isControllableChanged();

private:
    QString m_name;
    qreal m_speed = 0;
    qreal m_rpm = 0;
    bool m_isControllable = 0;

    QKlipperConsole *m_console = nullptr;

    Q_PROPERTY(QString name READ name RESET resetName NOTIFY nameChanged FINAL)
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed RESET resetSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(qreal rpm READ rpm RESET resetRpm NOTIFY rpmChanged FINAL)
    Q_PROPERTY(bool isControllable READ isControllable RESET resetIsControllable NOTIFY isControllableChanged FINAL)
};

#endif // QKLIPPERFAN_H
