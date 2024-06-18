#ifndef QWEBCAMFRAME_H
#define QWEBCAMFRAME_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QLabel>

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

    void setSource(QString &source);
    void setTitle(QString &title);
    void showInfo();
    void hideInfo();

    void play();
    void pause();
    void stop();

protected:
    virtual void resizeEvent(QResizeEvent *event);

protected slots:
    void on_playbackRateChanged(qreal rate);

private:
    QGridLayout *_layout = nullptr;
    QGraphicsScene *_scene = nullptr;
    QGraphicsView *_view = nullptr;
    QGraphicsVideoItem *_video = nullptr;
    QMediaPlayer *_player = nullptr;

    QLabel *_nameLabel = nullptr;
    QLabel *_infoLabel = nullptr;

    bool _showInfo = false;
};

#endif // QWEBCAMFRAME_H
