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

#ifndef QKLIPPERMCU_H
#define QKLIPPERMCU_H

#include <QObject>

class QKlipperSystem;
class QKlipperConsole;

//TODO This will likely become a Q_GADGET since it doesn't control anything

//!  QKlipperMCU class
/*!
  This class is responsible for holding the data related to the current MCU. There are no methods
  to change any of the parameters and all changes must be done in the configuration files
*/
class QKlipperMCU : public QObject
{
    Q_OBJECT

    friend QKlipperSystem;
    friend QKlipperConsole;
public:
    /*!
     * Constructor
     *
     * \param parent The parent object
     */
    explicit QKlipperMCU(QObject *parent = nullptr);

    QKlipperMCU(const QKlipperMCU &value);
    QKlipperMCU(QKlipperMCU &&value);
    QKlipperMCU &operator=(const QKlipperMCU &value);
    QKlipperMCU &operator=(QKlipperMCU &&value);
    bool operator==(const QKlipperMCU &value);
    bool operator==(QKlipperMCU &&value);
    bool operator!=(const QKlipperMCU &value);
    bool operator!=(QKlipperMCU &&value);

    /*!
     * Baud rate of the MCU's serial device
     *
     * \returns The baud rate
     */
    qint64 baudRate() const;

    /*!
     * Number of sequences received
     *
     * \returns The number of sequences received
     */
    qint64 sequenceRecieved() const;

    /*!
     * Number of sequences sent
     *
     * \returns The number of sequences sent
     */
    qint64 sequenceSent() const;

    /*!
     * Number of sequences re-sent after failure
     *
     * \returns The number of sequences re-sent
     */
    qint64 sequenceRetransmitted() const;

    /*!
     * Number of bytes received that were invalid
     *
     * \returns The number of bytes that were invalid
     */
    qint64 bytesInvalid() const;

    /*!
     * Number of bytes received that were read
     *
     * \returns The number of bytes that were read
     */
    qint64 bytesRead() const;

    /*!
     * Number of bytes received that were retransmitted
     *
     * \returns The number of bytes that were retransmitted
     */
    qint64 bytesRetransmitted() const;

    /*!
     * Number of bytes sent that were actually written
     *
     * \returns The number of bytes that were written
     */
    qint64 bytesWritten() const;

    /*!
     * Number of bytes that are going to be received
     *
     * \returns The number of bytes that are going to be received
     */
    qint64 bytesUpcoming() const;

    /*!
     * Number of bytes that are available to be read
     *
     * \returns The number of bytes that are available to be read
     */
    qint64 bytesAvailable() const;

    /*!
     * Frequency of the MCU (Hz)
     *
     * \returns Frequency of the MCU (Hz)
     */
    qint64 frequency() const;

    /*!
     * Serial ID of the MCU
     *
     * \returns Serial ID of the MCU
     */
    QString serial() const;

    /*!
     * Firmware version of the MCU
     *
     * \returns Firmware version of the MCU
     */
    QString firmwareVersion() const;

    /*!
     * Hardware version of the MCU
     *
     * \returns Hardware version of the MCU
     */
    QString hardwareVersion() const;

    /*!
     * Uptime of the MCU
     *
     * \returns Uptime of the MCU
     */
    qreal awake() const;

    /*!
     * Average task time of the MCU
     *
     * \returns Average task time of the MCU
     */
    qreal taskAverage() const;

    /*!
     * Average dev time of the MCU
     *
     * \returns Average task dev of the MCU
     */
    qreal devAverage() const;

    /*!
     * Max stepper error setting of the MCU
     *
     * \returns Max stepper error setting of the MCU
     */
    qreal maxStepperError() const;

private slots:

    //TODO: rename all functions here to end with Data
    void setBaudRate(qint64 baudRate);

    void setSequenceRecieved(qint64 sequenceRecieved);

    void setSequenceSent(qint64 sequenceSent);

    void setSequenceRetransmitted(qint64 sequenceRetransmitted);

    void setBytesInvalid(qint64 bytesInvalid);

    void setBytesRead(qint64 bytesRead);

    void setBytesRetransmitted(qint64 bytesRetransmitted);

    void setBytesWritten(qint64 bytesWritten);

    void setBytesUpcoming(qint64 bytesUpcoming);

    void setBytesAvailable(qint64 bytesAvailable);

    void setFrequency(qint64 frequency);

    void setSerial(const QString &serial);

    void setFirmwareVersion(const QString &firmwareVersion);

    void setHardwareVersion(const QString &hardwareVersion);

    void setAwake(qreal awake);

    void setTaskAverage(qreal taskAverage);

    void setDevAverage(qreal devAverage);

    void setMaxStepperError(qreal maxStepperError);

signals:

    void baudRateChanged();
    void sequenceRecievedChanged();
    void sequenceSentChanged();
    void sequenceRetransmittedChanged();
    void bytesInvalidChanged();
    void bytesReadChanged();
    void bytesRetransmittedChanged();
    void bytesWrittenChanged();
    void bytesUpcomingChanged();
    void bytesAvailableChanged();
    void frequencyChanged();
    void serialChanged();
    void firmwareVersionChanged();
    void hardwareVersionChanged();
    void awakeChanged();
    void taskAverageChanged();
    void devAverageChanged();
    void maxStepperErrorChanged();

private:
    qint64 m_baudRate = 0;
    qint64 m_sequenceRecieved = 0;
    qint64 m_sequenceSent = 0;
    qint64 m_sequenceRetransmitted = 0;
    qint64 m_bytesInvalid = 0;
    qint64 m_bytesRead = 0;
    qint64 m_bytesRetransmitted = 0;
    qint64 m_bytesWritten = 0;
    qint64 m_bytesUpcoming = 0;
    qint64 m_bytesAvailable = 0;
    qint64 m_frequency = 0;

    QString m_serial;
    QString m_firmwareVersion;
    QString m_hardwareVersion;

    qreal m_awake = 0.0;
    qreal m_taskAverage = 0.0;
    qreal m_devAverage = 0.0;
    qreal m_maxStepperError = 0;

    Q_PROPERTY(qint64 baudRate READ baudRate WRITE setBaudRate NOTIFY baudRateChanged FINAL)
    Q_PROPERTY(qint64 sequenceRecieved READ sequenceRecieved WRITE setSequenceRecieved NOTIFY sequenceRecievedChanged FINAL)
    Q_PROPERTY(qint64 sequenceSent READ sequenceSent WRITE setSequenceSent NOTIFY sequenceSentChanged FINAL)
    Q_PROPERTY(qint64 sequenceRetransmitted READ sequenceRetransmitted WRITE setSequenceRetransmitted NOTIFY sequenceRetransmittedChanged FINAL)
    Q_PROPERTY(qint64 bytesInvalid READ bytesInvalid WRITE setBytesInvalid NOTIFY bytesInvalidChanged FINAL)
    Q_PROPERTY(qint64 bytesRead READ bytesRead WRITE setBytesRead NOTIFY bytesReadChanged FINAL)
    Q_PROPERTY(qint64 bytesRetransmitted READ bytesRetransmitted WRITE setBytesRetransmitted NOTIFY bytesRetransmittedChanged FINAL)
    Q_PROPERTY(qint64 bytesWritten READ bytesWritten WRITE setBytesWritten NOTIFY bytesWrittenChanged FINAL)
    Q_PROPERTY(qint64 bytesUpcoming READ bytesUpcoming WRITE setBytesUpcoming NOTIFY bytesUpcomingChanged FINAL)
    Q_PROPERTY(qint64 bytesAvailable READ bytesAvailable WRITE setBytesAvailable NOTIFY bytesAvailableChanged FINAL)
    Q_PROPERTY(qint64 frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged FINAL)
    Q_PROPERTY(QString serial READ serial WRITE setSerial NOTIFY serialChanged FINAL)
    Q_PROPERTY(QString firmwareVersion READ firmwareVersion WRITE setFirmwareVersion NOTIFY firmwareVersionChanged FINAL)
    Q_PROPERTY(QString hardwareVersion READ hardwareVersion WRITE setHardwareVersion NOTIFY hardwareVersionChanged FINAL)
    Q_PROPERTY(qreal awake READ awake WRITE setAwake NOTIFY awakeChanged FINAL)
    Q_PROPERTY(qreal taskAverage READ taskAverage WRITE setTaskAverage NOTIFY taskAverageChanged FINAL)
    Q_PROPERTY(qreal devAverage READ devAverage WRITE setDevAverage NOTIFY devAverageChanged FINAL)
    Q_PROPERTY(qreal maxStepperError READ maxStepperError WRITE setMaxStepperError NOTIFY maxStepperErrorChanged FINAL)
};

#endif // QKLIPPERMCU_H
