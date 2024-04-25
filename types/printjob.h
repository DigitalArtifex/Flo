#ifndef PRINTJOB_H
#define PRINTJOB_H

#define DEBUG_PRINTJOB

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>

class Printer;

class PrintJob : public QObject
{
    Q_OBJECT
public:

    enum JobState {
        Standby,
        Printing,
        Paused,
        Complete,
        Cancelled,
        Error
    };

    PrintJob(Printer *parent);
    ~PrintJob();

    JobState state() const;
    void setState(JobState state);
    void setState(QString state);

    QString filename() const;
    void setFilename(const QString &filename);

    QString message() const;
    void setMessage(const QString &message);

    qreal totalDuration() const;
    void setTotalDuration(qreal totalDuration);

    qreal printDuration() const;
    void setPrintDuration(qreal printDuration);

    qreal filamentUsed() const;
    void setFilamentUsed(qreal filamentUsed);

    qint64 totalLayers() const;
    void setTotalLayers(qint64 totalLayers);

    qint64 currentLayer() const;
    void setCurrentLayer(qint64 currentLayer);

    Printer *parent() const;

signals:
    void started(PrintJob *job);
    void finished(PrintJob *job);
    void cancelled(PrintJob *job);
    void error(PrintJob *job);
    void paused(PrintJob *job);
    void resumed(PrintJob *job);
    void standby(PrintJob *job);
    void updated(PrintJob *job);

protected slots:

#ifdef DEBUG_PRINTJOB
    void on_printJobTestTimer_timeout();
#endif

private:

#ifdef DEBUG_PRINTJOB
    QTimer *_printJobTestTimer = nullptr;
#endif

    JobState _state = Error;

    QString _filename;
    QString _message;

    qreal _totalDuration = 0.0;
    qreal _printDuration = 0.0;
    qreal _filamentUsed = 0.0;

    qint64 _totalLayers = 0;
    qint64 _currentLayer = 0;

    Printer *_parent = nullptr;
};

#endif // PRINTJOB_H
