/*
 *  Klipper Note:
 *  Note that these values are set by the SET_PRINT_STATS_INFO gcode command.
 *  It is necessary to configure the slicer to include this command in the print.
 *  SET_PRINT_STATS_INFO TOTAL_LAYER=total_layer_count should be called in the
 *  slicer's "start gcode" to initalize the total layer count.
 *  SET_PRINT_STATS_INFO CURRENT_LAYER=current_layer should be called in the
 *  slicer's "on layer change" gcode. The user must substitute the
 *  total_layer_count and current_layer with the appropriate "placeholder syntax"
 *  for the slicer.
 *
 */

#include "printjob.h"
#include "printer.h"

PrintJob::PrintJob(Printer *parent)
{
    _parent = parent;
#ifdef DEBUG_PRINTJOB
    _printJobTestTimer = new QTimer();
    _printJobTestTimer->setInterval(100);
    connect(_printJobTestTimer, SIGNAL(timeout()), this, SLOT(on_printJobTestTimer_timeout()));
    _printJobTestTimer->start();
#endif
}

PrintJob::~PrintJob()
{

}

PrintJob::JobState PrintJob::state() const
{
    return _state;
}

/*!
 * \brief PrintJob::setState handles the signalling of state changes in the job. Set this value last in updates
 * \param state
 */
void PrintJob::setState(JobState state)
{
    JobState oldState = _state;
    _state = state;

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
            else
                emit updated(this);
            break;
        case Paused:
            if(oldState != Paused)
                emit paused(this);
            else
                emit updated(this);
            break;
        case Complete:
            if(oldState != Complete)
            {
                emit updated(this);
                emit finished(this);
            }
            else
                emit updated(this);
            break;
        case Cancelled:
            if(oldState != Cancelled)
                emit cancelled(this);
            else
                emit updated(this);
            break;
        case Error:
            if(oldState != Error)
                emit error(this);
            else
                emit updated(this);
            break;
    }
}

/*!
 * \brief PrintJob::setState
 * handles the signalling of state changes in the job. Set this value last in updates
 * \param state
 */
void PrintJob::setState(QString state)
{
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

QString PrintJob::filename() const
{
    return _filename;
}

void PrintJob::setFilename(const QString &filename)
{
    _filename = filename;
}

QString PrintJob::message() const
{
    return _message;
}

void PrintJob::setMessage(const QString &message)
{
    _message = message;
}

qreal PrintJob::totalDuration() const
{
    return _totalDuration;
}

void PrintJob::setTotalDuration(qreal totalDuration)
{
    _totalDuration = totalDuration;
}

qreal PrintJob::printDuration() const
{
    return _printDuration;
}

void PrintJob::setPrintDuration(qreal printDuration)
{
    _printDuration = printDuration;
}

qreal PrintJob::filamentUsed() const
{
    return _filamentUsed;
}

void PrintJob::setFilamentUsed(qreal filamentUsed)
{
    _filamentUsed = filamentUsed;
}

qint64 PrintJob::totalLayers() const
{
    return _totalLayers;
}

void PrintJob::setTotalLayers(qint64 totalLayers)
{
    _totalLayers = totalLayers;
}

qint64 PrintJob::currentLayer() const
{
    return _currentLayer;
}

void PrintJob::setCurrentLayer(qint64 currentLayer)
{
    _currentLayer = currentLayer;
}

Printer *PrintJob::parent() const
{
    return _parent;
}

#ifdef DEBUG_PRINTJOB
void PrintJob::on_printJobTestTimer_timeout()
{
    quint32 lowPoint = QRandomGenerator::global()->generate();
    quint32 setPoint = QRandomGenerator::global()->generate();
    bool printToggle = setPoint > lowPoint;

    switch (_state)
    {
        case Standby:
            setFilename(QString("Test Job"));
            setCurrentLayer(0);
            setTotalLayers(QRandomGenerator::global()->generate());
            setTotalDuration(QRandomGenerator::global()->generate());
            setState(Printing);
            break;
        case Printing:
            if(printToggle)
                setState(Paused);
            else
            {
                setCurrentLayer(currentLayer() + (_totalLayers / 100));

                if(currentLayer() >= totalLayers())
                    setState(Complete);
                else
                    setState(Printing);
            }
            break;
        case Paused:
            if(printToggle)
                setState(Printing);
            break;
        case Complete:
            break;
        case Cancelled:
            break;
        case Error:
            break;
    }
}
#endif
