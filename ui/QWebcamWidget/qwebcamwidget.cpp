#include "qwebcamwidget.h"

QWebcamWidget::QWebcamWidget(QString source, QWidget *parent) : QFrame(parent)
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Subwidget"));

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

    setLayout(m_layout);

    m_videoLabel = new QLabel(this);
    m_videoLabel->setScaledContents(true);
    m_videoLabel->setFixedSize(size);
    m_layout->addWidget(m_videoLabel);

    m_webcamSink = new QVideoSink(this);

    m_player = new QMediaPlayer(m_videoLabel);
    m_player->setSource(source);
    m_player->setVideoSink(m_webcamSink);

    m_nameLabel = new QLabel(this);
    m_nameLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamTitle"));
    m_nameLabel->setVisible(false);

    m_infoLabel = new QLabel(this);
    m_infoLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamInfo"));
    m_infoLabel->setVisible(false);

    connect(m_webcamSink, SIGNAL(videoFrameChanged(QVideoFrame)), this, SLOT(videoFrameChangeEvent(QVideoFrame)));
    connect(m_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));

    //play();
    style()->polish(this);

    //connect(m_player, SIGNAL(playbackRateChanged(qreal)), this, SLOT(on_playbackRateChanged(qreal)));
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
    QWidget::resizeEvent(event);

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);
    qint32 width = event->size().width();
    width -= layout()->contentsMargins().left();
    width -= layout()->contentsMargins().right();
    width = qFloor(width);

    qint32 height = qFloor((qreal)width * ratio);

    size.setWidth(width);
    size.setHeight(height);

    if(m_videoLabel)
        m_videoLabel->setFixedSize(size);
}

void QWebcamWidget::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);
    pause();
}

void QWebcamWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    play();
}

void QWebcamWidget::on_playbackRateChanged(qreal rate)
{
    QString fps = QString::number(rate);
    m_infoLabel->setText(fps);
}

void QWebcamWidget::videoFrameChangeEvent(QVideoFrame frame)
{
    bool frameUpdate = false;

    if(m_lastFrameTime > 0)
    {
        qreal time = QDateTime::currentDateTime().toSecsSinceEpoch();
        qreal span = time - m_lastFrameTime;
        qreal threshold = (qreal)1/m_frameRate;

        if(span >= threshold)
            frameUpdate = true;
    }
    else
        frameUpdate = true;

    if(frameUpdate)
    {
        if(!frame.isValid())
            qDebug() << "invalid frame";

        QImage image = frame.toImage();
        m_videoLabel->setPixmap(QPixmap::fromImage(image));
    }
}

QString QWebcamWidget::info() const
{
    return m_info;
}

void QWebcamWidget::setInfo(const QString &info)
{
    m_info = info;
    m_infoLabel->setText(info);
}

QString QWebcamWidget::source() const
{
    return m_source;
}
