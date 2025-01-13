#include "qklippermcu.h"

QKlipperMCU::QKlipperMCU(QObject *parent)
    : QObject{parent}
{}

bool QKlipperMCU::operator==(const QKlipperMCU &value) const
{
    if(m_baudRate != value.m_baudRate) return false;
    if(m_sequenceRecieved != value.m_sequenceRecieved) return false;
    if(m_sequenceSent != value.m_sequenceSent) return false;
    if(m_sequenceRetransmitted != value.m_sequenceRetransmitted) return false;
    if(m_bytesInvalid != value.m_bytesInvalid) return false;
    if(m_bytesRead != value.m_bytesRead) return false;
    if(m_bytesRetransmitted != value.m_bytesRetransmitted) return false;
    if(m_bytesWritten != value.m_bytesWritten) return false;
    if(m_bytesUpcoming != value.m_bytesUpcoming) return false;
    if(m_bytesAvailable != value.m_bytesAvailable) return false;
    if(m_frequency != value.m_frequency) return false;

    if(m_serial != value.m_serial) return false;
    if(m_firmwareVersion != value.m_firmwareVersion) return false;
    if(m_hardwareVersion != value.m_hardwareVersion) return false;

    if(m_awake != value.m_awake) return false;
    if(m_taskAverage != value.m_taskAverage) return false;
    if(m_devAverage != value.m_devAverage) return false;
    if(m_maxStepperError != value.m_maxStepperError) return false;

    return true;
}

bool QKlipperMCU::operator!=(const QKlipperMCU &value)
{
    return !(*this == value);
}

qint64 QKlipperMCU::baudRate() const
{
    return m_baudRate;
}

void QKlipperMCU::setBaudRate(qint64 baudRate)
{
    if (m_baudRate == baudRate)
        return;
    m_baudRate = baudRate;
    emit baudRateChanged();
}

qint64 QKlipperMCU::sequenceRecieved() const
{
    return m_sequenceRecieved;
}

void QKlipperMCU::setSequenceRecieved(qint64 sequenceRecieved)
{
    if (m_sequenceRecieved == sequenceRecieved)
        return;
    m_sequenceRecieved = sequenceRecieved;
    emit sequenceRecievedChanged();
}

qint64 QKlipperMCU::sequenceSent() const
{
    return m_sequenceSent;
}

void QKlipperMCU::setSequenceSent(qint64 sequenceSent)
{
    if (m_sequenceSent == sequenceSent)
        return;
    m_sequenceSent = sequenceSent;
    emit sequenceSentChanged();
}

qint64 QKlipperMCU::sequenceRetransmitted() const
{
    return m_sequenceRetransmitted;
}

void QKlipperMCU::setSequenceRetransmitted(qint64 sequenceRetransmitted)
{
    if (m_sequenceRetransmitted == sequenceRetransmitted)
        return;
    m_sequenceRetransmitted = sequenceRetransmitted;
    emit sequenceRetransmittedChanged();
}

qint64 QKlipperMCU::bytesInvalid() const
{
    return m_bytesInvalid;
}

void QKlipperMCU::setBytesInvalid(qint64 bytesInvalid)
{
    if (m_bytesInvalid == bytesInvalid)
        return;
    m_bytesInvalid = bytesInvalid;
    emit bytesInvalidChanged();
}

qint64 QKlipperMCU::bytesRead() const
{
    return m_bytesRead;
}

void QKlipperMCU::setBytesRead(qint64 bytesRead)
{
    if (m_bytesRead == bytesRead)
        return;
    m_bytesRead = bytesRead;
    emit bytesReadChanged();
}

qint64 QKlipperMCU::bytesRetransmitted() const
{
    return m_bytesRetransmitted;
}

void QKlipperMCU::setBytesRetransmitted(qint64 bytesRetransmitted)
{
    if (m_bytesRetransmitted == bytesRetransmitted)
        return;
    m_bytesRetransmitted = bytesRetransmitted;
    emit bytesRetransmittedChanged();
}

qint64 QKlipperMCU::bytesWritten() const
{
    return m_bytesWritten;
}

void QKlipperMCU::setBytesWritten(qint64 bytesWritten)
{
    if (m_bytesWritten == bytesWritten)
        return;
    m_bytesWritten = bytesWritten;
    emit bytesWrittenChanged();
}

qint64 QKlipperMCU::bytesUpcoming() const
{
    return m_bytesUpcoming;
}

void QKlipperMCU::setBytesUpcoming(qint64 bytesUpcoming)
{
    if (m_bytesUpcoming == bytesUpcoming)
        return;
    m_bytesUpcoming = bytesUpcoming;
    emit bytesUpcomingChanged();
}

qint64 QKlipperMCU::bytesAvailable() const
{
    return m_bytesAvailable;
}

void QKlipperMCU::setBytesAvailable(qint64 bytesAvailable)
{
    if (m_bytesAvailable == bytesAvailable)
        return;
    m_bytesAvailable = bytesAvailable;
    emit bytesAvailableChanged();
}

qint64 QKlipperMCU::frequency() const
{
    return m_frequency;
}

void QKlipperMCU::setFrequency(qint64 frequency)
{
    if (m_frequency == frequency)
        return;
    m_frequency = frequency;
    emit frequencyChanged();
}

QString QKlipperMCU::serial() const
{
    return m_serial;
}

void QKlipperMCU::setSerial(const QString &serial)
{
    if (m_serial == serial)
        return;
    m_serial = serial;
    emit serialChanged();
}

QString QKlipperMCU::firmwareVersion() const
{
    return m_firmwareVersion;
}

void QKlipperMCU::setFirmwareVersion(const QString &firmwareVersion)
{
    if (m_firmwareVersion == firmwareVersion)
        return;
    m_firmwareVersion = firmwareVersion;
    emit firmwareVersionChanged();
}

QString QKlipperMCU::hardwareVersion() const
{
    return m_hardwareVersion;
}

void QKlipperMCU::setHardwareVersion(const QString &hardwareVersion)
{
    if (m_hardwareVersion == hardwareVersion)
        return;
    m_hardwareVersion = hardwareVersion;
    emit hardwareVersionChanged();
}

qreal QKlipperMCU::awake() const
{
    return m_awake;
}

void QKlipperMCU::setAwake(qreal awake)
{
    if (qFuzzyCompare(m_awake, awake))
        return;
    m_awake = awake;
    emit awakeChanged();
}

qreal QKlipperMCU::taskAverage() const
{
    return m_taskAverage;
}

void QKlipperMCU::setTaskAverage(qreal taskAverage)
{
    if (qFuzzyCompare(m_taskAverage, taskAverage))
        return;
    m_taskAverage = taskAverage;
    emit taskAverageChanged();
}

qreal QKlipperMCU::devAverage() const
{
    return m_devAverage;
}

void QKlipperMCU::setDevAverage(qreal devAverage)
{
    if (qFuzzyCompare(m_devAverage, devAverage))
        return;
    m_devAverage = devAverage;
    emit devAverageChanged();
}

qreal QKlipperMCU::maxStepperError() const
{
    return m_maxStepperError;
}

void QKlipperMCU::setMaxStepperError(qreal maxStepperError)
{
    if (qFuzzyCompare(m_maxStepperError, maxStepperError))
        return;
    m_maxStepperError = maxStepperError;
    emit maxStepperErrorChanged();
}
