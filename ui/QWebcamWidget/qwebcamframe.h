#ifndef QWEBCAMFRAME_H
#define QWEBCAMFRAME_H

#include <QObject>
#include <QVideoFrame>
#include <QWidget>

class QWebcamFrame : public QVideoFrame
{
    Q_OBJECT
public:
    QWebcamFrame();
};

#endif // QWEBCAMFRAME_H
