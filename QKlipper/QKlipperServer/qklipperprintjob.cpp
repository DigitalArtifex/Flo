#include "qklipperprintjob.h"

QKlipperPrintJob::QKlipperPrintJob(QObject *parent)
    : QObject{parent}
{}

QString QKlipperPrintJob::filename() const
{
    return m_filename;
}

void QKlipperPrintJob::setFilename(const QString &filename)
{
    if (m_filename == filename)
        return;

    m_filename = filename;
    emit filenameChanged();
}

QString QKlipperPrintJob::id() const
{
    return m_id;
}

void QKlipperPrintJob::setId(const QString &id)
{
    if (m_id == id)
        return;

    m_id = id;
    emit idChanged();
}

qreal QKlipperPrintJob::timeAdded() const
{
    return m_timeAdded;
}

void QKlipperPrintJob::setTimeAdded(qreal timeAdded)
{
    if (qFuzzyCompare(m_timeAdded, timeAdded))
        return;

    m_timeAdded = timeAdded;
    emit timeAddedChanged();
}

qreal QKlipperPrintJob::timeInQueue() const
{
    return m_timeInQueue;
}

void QKlipperPrintJob::setTimeInQueue(qreal timeInQueue)
{
    if (qFuzzyCompare(m_timeInQueue, timeInQueue))
        return;

    m_timeInQueue = timeInQueue;
    emit timeInQueueChanged();
}

QKlipperPrintJob::State QKlipperPrintJob::state() const
{
    return m_state;
}

/*!
 * \brief PrintJob::setState handles the signalling of state changes in the job. Set this value last in updates
 * \param state
 */
void QKlipperPrintJob::setState(State state)
{
    if (m_state == state)
        return;

    State oldState = m_state;
    m_state = state;

    switch(state)
    {
    case Standby:
        emit standby(this);
        break;
    case Printing:
        if(oldState == Paused)
            emit resumed(this);
        else if(oldState != Printing)
            emit started(this);
        break;
    case Paused:
        if(oldState != Paused)
            emit paused(this);
        break;
    case Complete:
        if(oldState != Complete)
            emit finished(this);
        break;
    case Cancelled:
        if(oldState != Cancelled)
            emit cancelled(this);
        break;
    case Error:
        if(oldState != Error)
            emit error(this);
        break;
    }

    emit stateChanged();
}

/*!
 * \brief PrintJob::setState
 * handles the signalling of state changes in the job. Set this value last in updates
 * \param state
 */
void QKlipperPrintJob::setState(QString state)
{
    state = state.toLower();

    if(state == QString("standby"))
        setState(Standby);
    else if(state == QString("printing"))
        setState(Printing);
    else if(state == QString("paused"))
        setState(Paused);
    else if(state == QString("complete"))
        setState(Complete);
    else if(state == QString("cancelled"))
        setState(Cancelled);
    else if(state == QString("error"))
        setState(Error);
}

QString QKlipperPrintJob::message() const
{
    return m_message;
}

void QKlipperPrintJob::setMessage(const QString &message)
{
    if (m_message == message)
        return;
    m_message = message;
    emit messageChanged();
}

qreal QKlipperPrintJob::totalDuration() const
{
    return m_totalDuration;
}

void QKlipperPrintJob::setTotalDuration(qreal totalDuration)
{
    if (qFuzzyCompare(m_totalDuration, totalDuration))
        return;
    m_totalDuration = totalDuration;
    emit totalDurationChanged();
}

qreal QKlipperPrintJob::printDuration() const
{
    return m_printDuration;
}

void QKlipperPrintJob::setPrintDuration(qreal printDuration)
{
    if (qFuzzyCompare(m_printDuration, printDuration))
        return;
    m_printDuration = printDuration;
    emit printDurationChanged();
}

qreal QKlipperPrintJob::filamentUsed() const
{
    return m_filamentUsed;
}

void QKlipperPrintJob::setFilamentUsed(qreal filamentUsed)
{
    if (qFuzzyCompare(m_filamentUsed, filamentUsed))
        return;
    m_filamentUsed = filamentUsed;
    emit filamentUsedChanged();
}

qint64 QKlipperPrintJob::totalLayers() const
{
    return m_totalLayers;
}

void QKlipperPrintJob::setTotalLayers(qint64 totalLayers)
{
    if (m_totalLayers == totalLayers)
        return;

    m_totalLayers = totalLayers;
    emit totalLayersChanged();
}

qint64 QKlipperPrintJob::currentLayer() const
{
    return m_currentLayer;
}

qreal QKlipperPrintJob::progress() const
{
    return ((qreal)m_currentLayer / (qreal)m_totalLayers);
}

void QKlipperPrintJob::setCurrentLayer(qint64 currentLayer)
{
    if (m_currentLayer == currentLayer)
        return;

    m_currentLayer = currentLayer;
    emit currentLayerChanged();
}
