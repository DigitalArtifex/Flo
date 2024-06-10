#include "qwebcamframe.h"

QWebcamFrame::QWebcamFrame(QWidget *parent) : QFrame(parent)
{
    _layout = new QGridLayout(this);
    _layout->setContentsMargins(0,0,0,0);

    _scene = new QGraphicsScene(this);
    _view = new QGraphicsView(_scene);

    _player = new QMediaPlayer;

    _video = new QGraphicsVideoItem;
    _video->setSize(_view->size());

    _view->scene()->addItem(_video);
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->show();

    _player->setVideoOutput(_video);

    _layout->addWidget(_view);

    _video->show();

    setLayout(_layout);
}

void QWebcamFrame::setSource(QString source)
{
    _player->setSource(source);
}

void QWebcamFrame::play()
{
    if(!_player->isPlaying())
        _player->play();
}

void QWebcamFrame::pause()
{
    if(_player->isPlaying())
        _player->pause();
}

void QWebcamFrame::stop()
{
    if(_player->isPlaying())
        _player->stop();
}

void QWebcamFrame::resizeEvent(QResizeEvent *event)
{
    _scene->setSceneRect(0,0,_view->width(),_view->height());
    _scene->setBackgroundBrush(QBrush(QColor::fromRgb(0,0,0)));
    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    _video->setSize(size);

    QFrame::resizeEvent(event);
}
