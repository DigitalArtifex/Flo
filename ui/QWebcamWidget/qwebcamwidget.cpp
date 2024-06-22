#include "qwebcamwidget.h"

QWebcamWidget::QWebcamWidget(QString source, QWidget *parent) : QWidget(parent)
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);

    setLayout(m_layout);

    m_nameLabel = new QLabel(this);
    m_nameLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamTitle"));
    m_nameLabel->setVisible(false);

    m_infoLabel = new QLabel(this);
    m_infoLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamInfo"));
    m_infoLabel->setVisible(false);

    m_videoLabel = new QLabel(this);
    m_videoLabel->setScaledContents(true);
    m_layout->addWidget(m_videoLabel);

    m_webcamSink = new QVideoSink(this);

    m_player = new QMediaPlayer(m_videoLabel);
    m_player->setSource(source);
    m_player->setVideoSink(m_webcamSink);
    //_player->setVideoOutput(m_videoLabel);
    connect(m_webcamSink, SIGNAL(videoFrameChanged(QVideoFrame)), this, SLOT(videoFrameChangeEvent(QVideoFrame)));

    connect(m_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));

    play();
    update();

    connect(m_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));
}

QWebcamWidget::~QWebcamWidget()
{
    if(m_videoLabel)
    {
        m_layout->removeWidget(m_videoLabel);
        m_videoLabel->deleteLater();
    }

    if(m_nameLabel)
        m_nameLabel->deleteLater();

    if(m_infoLabel)
        m_infoLabel->deleteLater();

    if(m_webcamSink)
        m_webcamSink->deleteLater();

    if(m_player)
        m_player->deleteLater();

    if(m_layout)
        delete m_layout;
}

void QWebcamWidget::setSource(QString &source)
{
    if(m_player)
        m_player->setSource(source);

    m_source = source;
}

void QWebcamWidget::setTitle(QString &title)
{
    m_nameLabel->setText(title);
    m_nameLabel->setVisible(true);
}

void QWebcamWidget::showInfo()
{
    m_showInfo = true;
    m_infoLabel->setHidden(false);
}

void QWebcamWidget::hideInfo()
{
    m_showInfo = false;
    m_infoLabel->setHidden(true);
}

void QWebcamWidget::play()
{
    if(m_player && !m_player->isPlaying())
        m_player->play();
}

void QWebcamWidget::pause()
{
    if(m_player && m_player->isPlaying())
        m_player->pause();
}

void QWebcamWidget::stop()
{
    if(m_player && m_player->isPlaying())
        m_player->stop();
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

    if(m_videoLabel)
        m_videoLabel->resize(size);

    QWidget::resizeEvent(event);
}

void QWebcamWidget::hideEvent(QHideEvent *event)
{
    /*
    qDebug() << "hiding";

    if(m_player)
    {
        stop();

        delete m_player;
        m_player = nullptr;
    }

    if(m_videoLabel)
    {
        delete m_videoLabel;
        m_videoLabel = nullptr;
    }
    */
    QWidget::hideEvent(event);
}

void QWebcamWidget::showEvent(QShowEvent *event)
{
    /*
    if(!m_source.isEmpty() && !m_player)
    {
        if(!m_videoLabel)
        {
            m_videoLabel = new QVideoWidget(this);
            m_videoLabel->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
            m_layout->addWidget(m_videoLabel);
        }

        m_player = new QMediaPlayer(m_videoLabel);
        m_player->setSource(m_source);
        m_player->setVideoOutput(m_videoLabel);

        connect(m_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));

        play();
        update();
    }*/

    QWidget::showEvent(event);
}

void QWebcamWidget::on_playbackRateChanged(qreal rate)
{
    QString fps = QString::number(rate);
    m_infoLabel->setText(fps);
    update();
}

void QWebcamWidget::videoFrameChangeEvent(QVideoFrame frame)
{
    if(!frame.isValid())
        qDebug() << "invalid frame";

    QImage image = frame.toImage();
    m_videoLabel->setPixmap(QPixmap::fromImage(image).scaledToWidth(m_videoLabel->width(), Qt::SmoothTransformation));
    update();
}

QString QWebcamWidget::info() const
{
    return m_info;
}

void QWebcamWidget::setInfo(const QString &info)
{
    m_info = info;
    //_infoLabel->setText(info);
}

QString QWebcamWidget::source() const
{
    return m_source;
}
