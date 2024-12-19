#include "qwebcamwidget.h"

#include "system/settings.h"

QWebcamWidget::QWebcamWidget(QString source, int timeout, QWidget *parent) : QWidget(parent)
{
    setupUi();

    m_timeout = timeout;

    m_webcamThread = new QThread(this);
    m_webcamSource = new QWebcamSource(m_timeout, m_webcamThread);
    m_webcamSource->setSource(source);
    m_webcamSource->moveToThread(m_webcamThread);

    connect(m_webcamSource, SIGNAL(frameChanged(QVideoFrame)), this, SLOT(videoFrameChangeEvent(QVideoFrame)));
    connect(m_webcamSource, SIGNAL(stateChanged()), this, SLOT(webcamSourceStateChanged()));
    setupIcons();
}

QWebcamWidget::~QWebcamWidget()
{
    if(m_webcamThread)
    {
        if(m_webcamSource)
        {
            m_webcamSource->moveToThread(QThread::currentThread());
            m_webcamSource->stop();
            m_webcamSource->deleteLater();
        }

        if(m_webcamThread->isRunning())
            m_webcamThread->exit();

        m_webcamThread->deleteLater();
    }

    if(m_videoLabel)
    {
        m_layout->removeWidget(m_videoLabel);
        m_videoLabel->deleteLater();
    }

    if(m_nameLabel)
    {
        m_layout->removeWidget(m_videoLabel);
        m_nameLabel->deleteLater();
    }

    if(m_infoLabel)
    {
        m_layout->removeWidget(m_videoLabel);
        m_infoLabel->deleteLater();
    }

    if(m_layout)
        m_layout->deleteLater();
}

void QWebcamWidget::setStateIcon(QWebcamSource::State state, QIcon icon)
{
    for(QWebcamSource::State stateFlag = (QWebcamSource::State)1; stateFlag <= QWebcamSource::Timeout; stateFlag = QWebcamSource::State(stateFlag << 1))
    {
        if((state & stateFlag) == stateFlag)
            m_iconMap[stateFlag] = icon;
    }

    setupIcons();
}

void QWebcamWidget::setSource(QString &source)
{
    m_webcamSource->setSource(source);
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
    m_webcamSource->play();
}

void QWebcamWidget::pause()
{
    m_webcamSource->pause();
}

void QWebcamWidget::stop()
{
    m_webcamSource->stop();
}

void QWebcamWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if(m_overlayWidget)
        m_overlayWidget->resize(event->size());
}

void QWebcamWidget::hideEvent(QHideEvent *event)
{
    pause();
    QWidget::hideEvent(event);
}

void QWebcamWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    play();
}

void QWebcamWidget::paintEvent(QPaintEvent *event)
{
    if(!m_lastFrame.isNull())
    {
        QPainter painter;

        painter.begin(this);
        painter.setRenderHint(QPainter::LosslessImageRendering);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.drawPixmap(rect(), m_lastFrame, m_lastFrame.rect());
        painter.end();
    }

    QWidget::paintEvent(event);
}

void QWebcamWidget::on_playbackRateChanged(qreal rate)
{
    QString fps = QString::number(rate);
    m_infoLabel->setText(fps);
}

void QWebcamWidget::videoFrameChangeEvent(QVideoFrame frame)
{
    if(frame.isValid())
    {
        m_lastFrame = QPixmap::fromImage(frame.toImage());

        if(m_lastFrame.size() != size())
            m_lastFrame.scaled(size(), Qt::KeepAspectRatio, Qt::FastTransformation);

        setupIcons();

        emit frameChanged();
        update();
    }
}

void QWebcamWidget::webcamSourceStateChanged()
{
    switch(m_webcamSource->state())
    {
        case QWebcamSource::Connecting:
            if(m_overlayWidget)
            {
                m_overlayTextLabel->setText("Connecting");
                m_overlayWidget->raise();
                m_overlayWidget->setHidden(false);
            }
            break;
        case QWebcamSource::Connected:
            if(m_overlayWidget)
            {
                m_overlayTextLabel->setText("Connected");
                m_overlayWidget->raise();
                m_overlayWidget->setHidden(true);
            }
            break;
        case QWebcamSource::Paused:
            if(m_overlayWidget)
            {
                m_overlayTextLabel->setText("Paused");
                m_overlayWidget->raise();
                m_overlayWidget->setHidden(false);
            }
            break;
        case QWebcamSource::None:
        case QWebcamSource::NoConnection:
            if(m_overlayWidget)
            {
                m_overlayTextLabel->setText("No Connection");
                m_overlayWidget->raise();
                m_overlayWidget->setHidden(false);
            }
            break;
        case QWebcamSource::InvalidFrame:
            if(m_overlayWidget)
            {
                m_overlayTextLabel->setText("Invalid Frame");
                m_overlayWidget->raise();
                m_overlayWidget->setHidden(false);
            }
            break;
        case QWebcamSource::Timeout:
            if(m_overlayWidget)
            {
                m_overlayTextLabel->setText("Problem Connecting To Webcam");
                m_overlayWidget->raise();
                m_overlayWidget->setHidden(false);
            }
            break;
    }

    setupIcons();
}

QWebcamSource::State QWebcamWidget::state() const
{
    return m_webcamSource->state();
}

void QWebcamWidget::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamWidget"));

    setLayout(m_layout);

    m_nameLabel = new QLabel(this);
    m_nameLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamTitle"));
    m_nameLabel->setVisible(false);

    m_infoLabel = new QLabel(this);
    m_infoLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "WebcamInfo"));
    m_infoLabel->setVisible(false);

    m_overlayWidget = new QWidget(this);
    m_overlayWidget->setGeometry(geometry());
    m_overlayWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_overlayLayout = new QGridLayout(m_overlayWidget);
    m_overlayLayout->setContentsMargins(0,0,0,0);
    m_infoLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PopupOverlay"));
    m_overlayWidget->setLayout(m_layout);

    m_overlayTopSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_overlayLayout->addItem(m_overlayTopSpacer,0,0);

    m_overlayIconLabel = new QLabel(this);
    m_overlayIconLabel->setFixedSize(32,32);
    m_overlayLayout->addWidget(m_overlayIconLabel, 1, 0, Qt::AlignCenter);

    m_overlayTextLabel = new QLabel(this);
    m_overlayTextLabel->setText(QString("No connection"));
    m_overlayTextLabel->setAlignment(Qt::AlignHCenter);
    m_overlayLayout->addWidget(m_overlayTextLabel, 2, 0, Qt::AlignCenter);

    m_overlayBottomSpacer = new QSpacerItem(10,10, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_overlayLayout->addItem(m_overlayBottomSpacer,3,0);
}

QPixmap QWebcamWidget::lastFrame() const
{
    return m_lastFrame;
}

void QWebcamWidget::setupIcons()
{
    if(m_iconMap.contains(m_webcamSource->state()))
    {
        QPixmap pixmap = m_iconMap[m_webcamSource->state()].pixmap(m_iconSize);
        m_overlayIconLabel->setPixmap(pixmap);
    }
}

void QWebcamWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::StyleChange)
    {
        setupIcons();
    }

    QWidget::changeEvent(event);
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
    return m_webcamSource->source().toString();
}
