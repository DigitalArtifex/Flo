#ifndef PRINTJOB_H
#define PRINTJOB_H

#include <QObject>

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

signals:
    void started();
    void finished();
    void cancelled();
    void error();
    void paused();
    void resumed();
    void standby();
    void updated();

private:
    JobState _state = Error;

    QString _filename;
    QString _message;

    qreal _totalDuration = 0.0;
    qreal _printDuration = 0.0;
    qreal _filamentUsed = 0.0;

    qint64 _totalLayers = 0;
    qint64 _currentLayer = 0;
};

#endif // PRINTJOB_H
