#include "printerwebcamwidget.h"

PrinterWebcamWidget::PrinterWebcamWidget(QKlipperInstance *instance, QWidget *parent) :
    QFrame(parent)
{
    m_instance = instance;

    setupUi();
    setupUiClasses();

    connect(m_instance, SIGNAL(connected(QKlipperInstance*)), this, SLOT(onInstanceOnline(QKlipperInstance*)));
    connect(m_instance, SIGNAL(disconnected(QKlipperInstance*)), this, SLOT(onInstanceOffline(QKlipperInstance*)));
}

PrinterWebcamWidget::~PrinterWebcamWidget()
{
    // if(m_webcamFrame)
    //     m_webcamFrame->deleteLater();

    // if(m_webcamFrame_1)
    //     m_webcamFrame->deleteLater();

    // if(m_webcamFrame_2)
    //     m_webcamFrame->deleteLater();

    // if(m_webcamFrame_3)
    //     m_webcamFrame->deleteLater();

    // if(m_thumbnailTimer)
    //     m_thumbnailTimer->deleteLater();

    // if(m_emptyFrame)
    //     m_emptyFrame->deleteLater();

    // if(m_layout)
    //     m_layout->deleteLater();
}

void PrinterWebcamWidget::setStyleSheet(const QString &styleSheet)
{
    setupIcons();

    if(m_webcamFrame)
        m_webcamFrame->setStyleSheet(styleSheet);

    if(m_webcamFrame_1)
        m_webcamFrame_1->setStyleSheet(styleSheet);

    if(m_webcamFrame_2)
        m_webcamFrame_2->setStyleSheet(styleSheet);

    if(m_webcamFrame_3)
        m_webcamFrame_3->setStyleSheet(styleSheet);

    QFrame::setStyleSheet(styleSheet);
}

void PrinterWebcamWidget::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    setLayout(m_layout);

    setupWebcam0();

    m_emptyFrame = new EmptyPrinterWebcamFrame(this);
    m_emptyFrame->setFixedSize(geometry().size());
    m_emptyFrame->raise();
    m_emptyFrame->setHidden(true);
}

void PrinterWebcamWidget::setupUiClasses()
{
}

void PrinterWebcamWidget::setupIcons()
{

}

void PrinterWebcamWidget::setupWebcam0()
{
    //setup primary webcam

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(!m_webcamFrame)
    {
        m_webcamFrame = new QWebcamWidget(m_webcamUrl, this);
        m_webcamFrame->resize(size);
        m_webcamFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_layout->addWidget(m_webcamFrame, 0, 0, 1, 3, Qt::AlignCenter);
    }

    m_webcamFrame->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam1()
{
    //setup primary webcam

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(!m_webcamFrame_1)
    {
        m_webcamFrame_1 = new QWebcamWidget(m_webcamUrl, this);
        m_webcamFrame_1->resize(size);
        m_layout->addWidget(m_webcamFrame_1, 1, 0, 1, 1, Qt::AlignCenter);
    }

    m_webcamFrame_1->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam2()
{
    //setup primary webcam

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(!m_webcamFrame_2)
    {
        m_webcamFrame_2 = new QWebcamWidget(m_webcamUrl, this);
        m_webcamFrame_2->resize(size);
        m_layout->addWidget(m_webcamFrame_2, 1, 1, 1, 1, Qt::AlignCenter);
    }

    m_webcamFrame_2->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam3()
{
    //setup primary webcam

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(!m_webcamFrame_3)
    {
        m_webcamFrame_3 = new QWebcamWidget(m_webcamUrl, this);
        m_webcamFrame_3->resize(size);
        m_layout->addWidget(m_webcamFrame_3, 1, 2, 1, 1, Qt::AlignCenter);
    }

    m_webcamFrame_3->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::onSystemWebcamsChanged()
{
    if(m_instance->system()->webcams().count() > 0 && m_webcamIndex == -1)
    {
        for(int i = 0; i < m_instance->system()->webcams().count(); i++)
        {
            QKlipperWebcam webcam = m_instance->system()->webcams()[i];

            if(i == 0)
            {
                QString url = m_instance->server()->address() + webcam.streamUrl();

                if(url.contains(QString(":%1").arg(m_instance->port())))
                    url.remove(QString(":%1").arg(m_instance->port()));

                m_webcamUrl = url;

                if(m_webcamFrame)
                {
                    QString fps = QString::number(webcam.targetFps());

                    if(m_webcamFrame->source() != url)
                    {
                        m_webcamFrame->stop();
                        m_webcamFrame->setSource(url);
                        m_webcamFrame->play();
                    }

                    QString name = webcam.name();

                    m_webcamFrame->setInfo(fps);
                    m_webcamFrame->setTitle(name);
                }
            }

            else if(i == 1)
            {
                QString url = m_instance->server()->address() + webcam.streamUrl();

                m_webcamUrl_1 = url;

                if(m_webcamFrame_1)
                {
                    QString fps = QString::number(webcam.targetFps());

                    if(m_webcamFrame_1->source() != url)
                    {
                        m_webcamFrame_1->stop();
                        m_webcamFrame_1->setSource(url);
                        m_webcamFrame_1->play();
                    }

                    QString name = webcam.name();

                    m_webcamFrame->setInfo(fps);
                    m_webcamFrame->setTitle(name);
                }
            }

            else if(i == 2)
            {
                QString url = m_instance->server()->address() + webcam.streamUrl();

                m_webcamUrl_2 = url;

                if(m_webcamFrame_2)
                {
                    QString fps = QString::number(webcam.targetFps());

                    if(m_webcamFrame_2->source() != url)
                    {
                        m_webcamFrame_2->stop();
                        m_webcamFrame_2->setSource(url);
                        m_webcamFrame_2->play();
                    }

                    QString name = webcam.name();

                    m_webcamFrame->setInfo(fps);
                    m_webcamFrame->setTitle(name);
                }
            }

            else if(i == 3)
            {
                QString url = m_instance->server()->address() + webcam.streamUrl();

                m_webcamUrl_3 = url;

                if(m_webcamFrame_3)
                {
                    QString fps = QString::number(webcam.targetFps());

                    if(m_webcamFrame_3->source() != url)
                    {
                        m_webcamFrame_3->stop();
                        m_webcamFrame_3->setSource(url);
                        m_webcamFrame_3->play();
                    }

                    QString name = webcam.name();

                    m_webcamFrame->setInfo(fps);
                    m_webcamFrame->setTitle(name);
                }
            }
        }

        m_webcamIndex = 0;

        if(m_emptyFrame)
        {
            m_emptyFrame->lower();
            m_emptyFrame->setHidden(true);
        }
    }
    else
    {
        if(m_emptyFrame && m_emptyFrame->isHidden())
        {
            m_emptyFrame->raise();
            m_emptyFrame->setHidden(false);
        }
    }
}

void PrinterWebcamWidget::onInstanceOnline(QKlipperInstance *instance)
{
    onSystemWebcamsChanged();
    connect(m_instance->system(), SIGNAL(webcamsChanged()), this, SLOT(onSystemWebcamsChanged()));

    if(!m_thumbnailTimer)
    {
        m_thumbnailTimer = new QTimer(this);
        m_thumbnailTimer->setInterval(5000);
        m_thumbnailTimer->start();

        connect(m_thumbnailTimer, SIGNAL(timeout()), this, SLOT(onWebcamThumbnailUpdate()));
    }
}

void PrinterWebcamWidget::onInstanceOffline(QKlipperInstance *instance)
{
    if(m_webcamFrame)
        m_webcamFrame->stop();

    if(m_webcamFrame_1)
        m_webcamFrame_1->stop();

    if(m_webcamFrame_2)
        m_webcamFrame_2->stop();

    if(m_webcamFrame_3)
        m_webcamFrame_3->stop();

    if(m_thumbnailTimer)
        m_thumbnailTimer->stop();

    disconnect(m_instance->system(), SIGNAL(webcamsChanged()), this, SLOT(onSystemWebcamsChanged()));
}

void PrinterWebcamWidget::onWebcamThumbnailUpdate()
{
    m_instance->setThumbnail(m_webcamFrame->lastFrame().toImage());
}

void PrinterWebcamWidget::resizeEvent(QResizeEvent *event)
{
    if(m_emptyFrame)
        m_emptyFrame->setGeometry(this->geometry());

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)qFloor((width() - 10) * ratio)));

    if(m_webcamFrame)
    {
        m_webcamFrame->resize(size);
        m_webcamFrame->setMaximumSize(size);
        m_webcamFrame->setMinimumSize(size);
    }

    //resize for other frames (1/3)
    size.setWidth((width() -12) / 3);
    size.setHeight(((width() -12) / 3) * ratio);

    if(m_webcamFrame_1)
    {
        m_webcamFrame_1->resize(size);
        m_webcamFrame_1->setMaximumSize(size);
    }
    if(m_webcamFrame_2)
    {
        m_webcamFrame_2->resize(size);
        m_webcamFrame_2->setMaximumSize(size);
    }
    if(m_webcamFrame_3)
    {
        m_webcamFrame_3->resize(size);
        m_webcamFrame_3->setMaximumSize(size);
    }

    QWidget::resizeEvent(event);
}

bool PrinterWebcamWidget::animating() const
{
    return m_animating;
}

void PrinterWebcamWidget::setAnimating(bool animating)
{
}
