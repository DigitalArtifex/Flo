#ifndef QWEBCAMFRAME_H
#define QWEBCAMFRAME_H

#include <QFrame>
#include <QObject>
#include <QWidget>

#include <QGraphicsView>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QGridLayout>

#include <QScrollBar>

#include <QResizeEvent>

class QWebcamFrame : public QFrame
{
public:
    QWebcamFrame(QWidget *parent);

    void setSource(QString source);

    void play();
    void pause();
    void stop();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:
    QGridLayout *_layout = nullptr;
    QGraphicsScene *_scene = nullptr;
    QGraphicsView *_view = nullptr;
    QGraphicsVideoItem *_video = nullptr;
    QMediaPlayer *_player = nullptr;
};

#endif // QWEBCAMFRAME_H
