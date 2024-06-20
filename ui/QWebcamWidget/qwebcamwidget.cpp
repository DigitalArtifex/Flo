#include "qwebcamwidget.h"

QWebcamWidget::QWebcamWidget(QString source, QWidget *parent) : QWidget(parent)
{
    _layout = new QGridLayout(this);
    _layout->setContentsMargins(0,0,0,0);

    setLayout(_layout);

    _nameLabel = new QLabel(this);
    _nameLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamTitle"));
    _nameLabel->setVisible(false);

    _infoLabel = new QLabel(this);
    _infoLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamInfo"));
    _infoLabel->setVisible(false);

    _videoLabel = new QLabel(this);
    _videoLabel->setScaledContents(true);
    _layout->addWidget(_videoLabel);

    _webcamSink = new QVideoSink(this);

    _player = new QMediaPlayer(_videoLabel);
    _player->setSource(source);
    _player->setVideoSink(_webcamSink);
    //_player->setVideoOutput(_videoLabel);
    connect(_webcamSink, SIGNAL(videoFrameChanged(QVideoFrame)), this, SLOT(videoFrameChangeEvent(QVideoFrame)));

    connect(_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));

    play();
    update();

    connect(_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));
}

QWebcamWidget::~QWebcamWidget()
{
    if(_videoLabel)
    {
        _layout->removeWidget(_videoLabel);
        _videoLabel->deleteLater();
    }

    if(_nameLabel)
        _nameLabel->deleteLater();

    if(_infoLabel)
        _infoLabel->deleteLater();

    if(_webcamSink)
        _webcamSink->deleteLater();

    if(_player)
        _player->deleteLater();

    if(_layout)
        delete _layout;
}

void QWebcamWidget::setSource(QString &source)
{
    if(_player)
        _player->setSource(source);

    _source = source;
}

void QWebcamWidget::setTitle(QString &title)
{
    _nameLabel->setText(title);
    _nameLabel->setVisible(true);
}

void QWebcamWidget::showInfo()
{
    _showInfo = true;
    _infoLabel->setHidden(false);
}

void QWebcamWidget::hideInfo()
{
    _showInfo = false;
    _infoLabel->setHidden(true);
}

void QWebcamWidget::play()
{
    if(_player && !_player->isPlaying())
        _player->play();
}

void QWebcamWidget::pause()
{
    if(_player && _player->isPlaying())
        _player->pause();
}

void QWebcamWidget::stop()
{
    if(_player && _player->isPlaying())
        _player->stop();
}

void QWebcamWidget::resizeEvent(QResizeEvent *event)
{
    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);
    qint32 width = this->width();
    width -= layout()->contentsMargins().left();
    width -= layout()->contentsMargins().right();
    width = qFloor(width);

    qint32 height = qFloor((qreal)width * ratio);

    size.setWidth(width);
    size.setHeight(height);

    if(_videoLabel)
        _videoLabel->resize(size);

    QWidget::resizeEvent(event);
}

void QWebcamWidget::hideEvent(QHideEvent *event)
{
    /*
    qDebug() << "hiding";

    if(_player)
    {
        stop();

        delete _player;
        _player = nullptr;
    }

    if(_videoLabel)
    {
        delete _videoLabel;
        _videoLabel = nullptr;
    }
    */
    QWidget::hideEvent(event);
}

void QWebcamWidget::showEvent(QShowEvent *event)
{
    /*
    if(!_source.isEmpty() && !_player)
    {
        if(!_videoLabel)
        {
            _videoLabel = new QVideoWidget(this);
            _videoLabel->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
            _layout->addWidget(_videoLabel);
        }

        _player = new QMediaPlayer(_videoLabel);
        _player->setSource(_source);
        _player->setVideoOutput(_videoLabel);

        connect(_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));

        play();
        update();
    }*/

    QWidget::showEvent(event);
}

void QWebcamWidget::on_playbackRateChanged(qreal rate)
{
    QString fps = QString::number(rate);
    _infoLabel->setText(fps);
    update();
}

void QWebcamWidget::videoFrameChangeEvent(QVideoFrame frame)
{
    if(!frame.isValid())
        qDebug() << "invalid frame";

    QImage image = frame.toImage();
    _videoLabel->setPixmap(QPixmap::fromImage(image).scaledToWidth(_videoLabel->width(), Qt::SmoothTransformation));
    update();
}

QString QWebcamWidget::info() const
{
    return _info;
}

void QWebcamWidget::setInfo(const QString &info)
{
    _info = info;
    //_infoLabel->setText(info);
}

QString QWebcamWidget::source() const
{
    return _source;
}
