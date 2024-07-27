#ifndef PRINTJOB_H
#define PRINTJOB_H

//#define DEBUG_PRINTJOB

#include <QObject>
#include <QTimer>

#ifdef DEBUG_PRINTJOB
#include <QRandomGenerator>
#endif

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
    QTimer *m_printJobTestTimer = nullptr;
#endif

    JobState m_state = Error;

    QString m_filename;
    QString m_message;

    qreal m_totalDuration = 0.0;
    qreal m_printDuration = 0.0;
    qreal m_filamentUsed = 0.0;

    qint64 m_totalLayers = 0;
    qint64 m_currentLayer = 0;

    Printer *m_parent = nullptr;
};

#endif // PRINTJOB_H
