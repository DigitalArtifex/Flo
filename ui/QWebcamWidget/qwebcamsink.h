#ifndef QWEBCAMSINK_H
#define QWEBCAMSINK_H

#include <QObject>
#include <QVideoSink>
#include <QWidget>

class QWebcamSink : public QVideoSink
{
    Q_OBJECT
public:
    QWebcamSink();
};

#endif // QWEBCAMSINK_H
