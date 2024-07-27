#include "printerwebcamwidget.h"

PrinterWebcamWidget::PrinterWebcamWidget(Printer *printer, QWidget *parent) :
    QFrame(parent)
{
    m_printer = printer;

    setupUi();
    setupUiClasses();

    m_delayTimer = new QTimer(this);
    m_delayTimer->setSingleShot(true);
    m_delayTimer->setInterval(2000);

    connect(m_printer, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printer_update(Printer*)));
}

PrinterWebcamWidget::~PrinterWebcamWidget()
{
    if(m_webcamFrame)
        delete m_webcamFrame;

    if(m_webcamFrame_1)
        delete m_webcamFrame;

    if(m_webcamFrame_2)
        delete m_webcamFrame;

    if(m_webcamFrame_3)
        delete m_webcamFrame;

    if(m_delayTimer)
        delete m_delayTimer;

    if(m_emptyFrame)
        delete m_emptyFrame;

    if(m_layout)
        delete m_layout;
}

void PrinterWebcamWidget::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    setIcons();

    update();
}

void PrinterWebcamWidget::setupUi()
{
    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0,0,0,0);
    setLayout(m_layout);

    //setup primary webcam

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(!m_webcamFrame)
    {
        qDebug() << QString("--setting stream url ") + m_webcamUrl;

        m_webcamFrame = new QWebcamWidget(m_webcamUrl, this);
        m_webcamFrame->resize(size);
        m_layout->addWidget(m_webcamFrame, 0, 0, 1, 1, Qt::AlignCenter);
        m_webcamFrame->play();
    }

    /*
    m_webcamFrame_1 = new QWebcamWidget(this);
    m_layout->addWidget(m_webcamFrame_1, 1, 0);

    m_webcamFrame_2 = new QWebcamWidget(this);
    m_layout->addWidget(m_webcamFrame_2, 1, 1);

    m_webcamFrame_3 = new QWebcamWidget(this);
    m_layout->addWidget(m_webcamFrame_3, 1, 2);*/

    m_emptyFrame = new EmptyPrinterWebcamFrame(this);
    m_emptyFrame->setFixedSize(geometry().size());
    m_emptyFrame->raise();
    m_emptyFrame->setHidden(true);
}

void PrinterWebcamWidget::setupUiClasses()
{
}

void PrinterWebcamWidget::setIcons()
{

}

void PrinterWebcamWidget::setupWebcam0()
{
    m_webcamFrame->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam1()
{
    m_webcamFrame_1->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam2()
{
    m_webcamFrame_2->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam3()
{
    m_webcamFrame_3->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::on_printer_update(Printer *printer)
{
    Q_UNUSED(printer);

    if(m_printer->system()->webcams().count() > 0 && m_webcamIndex == -1)
    {
        for(int i = 0; i < m_printer->system()->webcams().count(); i++)
        {
            System::Webcam webcam = m_printer->system()->webcams()[i];

            if(i == 0)
            {
                QString url = QString("http://") + m_printer->system()->hostname() + webcam.streamUrl;

                m_webcamUrl = url;

                if(m_webcamFrame)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(m_webcamFrame->source() != url)
                    {
                        m_webcamFrame->stop();
                        m_webcamFrame->setSource(url);
                        m_webcamFrame->play();
                    }

                    m_webcamFrame->setInfo(fps);
                    m_webcamFrame->setTitle(webcam.name);
                }
            }

            else if(i == 1)
            {
                QString url = QString("http://") + m_printer->system()->hostname() + webcam.streamUrl;

                m_webcamUrl_1 = url;

                if(m_webcamFrame_1)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(m_webcamFrame_1->source() != url)
                    {
                        m_webcamFrame_1->stop();
                        m_webcamFrame_1->setSource(url);
                        m_webcamFrame_1->play();
                    }

                    m_webcamFrame_1->setInfo(fps);
                    m_webcamFrame_1->setTitle(webcam.name);
                }
            }

            else if(i == 2)
            {
                QString url = QString("http://") + m_printer->system()->hostname() + webcam.streamUrl;

                m_webcamUrl_2 = url;

                if(m_webcamFrame_2)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(m_webcamFrame_2->source() != url)
                    {
                        m_webcamFrame_2->stop();
                        m_webcamFrame_2->setSource(url);
                        m_webcamFrame_2->play();
                    }

                    m_webcamFrame_2->setInfo(fps);
                    m_webcamFrame_2->setTitle(webcam.name);
                }
            }

            else if(i == 3)
            {
                QString url = QString("http://") + m_printer->system()->hostname() + webcam.streamUrl;

                m_webcamUrl_3 = url;

                if(m_webcamFrame_3)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(m_webcamFrame_3->source() != url)
                    {
                        m_webcamFrame_3->stop();
                        m_webcamFrame_3->setSource(url);
                        m_webcamFrame_3->play();
                    }

                    m_webcamFrame_3->setInfo(fps);
                    m_webcamFrame_3->setTitle(webcam.name);
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
        if(m_emptyFrame && !m_emptyFrame->isHidden())
        {
            m_emptyFrame->raise();
            m_emptyFrame->setHidden(false);
        }
    }
}

void PrinterWebcamWidget::resizeEvent(QResizeEvent *event)
{
    if(m_emptyFrame)
        m_emptyFrame->resize(event->size());

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(m_webcamFrame)
        m_webcamFrame->resize(size);

    //resize for other frames (1/3)
    size.setWidth((width() -12) / 3);
    size.setHeight(((width() -12) / 3) * ratio);

    if(m_webcamFrame_1)
        m_webcamFrame_1->resize(size);

    if(m_webcamFrame_2)
        m_webcamFrame_2->resize(size);

    if(m_webcamFrame_3)
        m_webcamFrame_3->resize(size);
}

bool PrinterWebcamWidget::animating() const
{
    return m_animating;
}

void PrinterWebcamWidget::setAnimating(bool animating)
{
    m_animating = animating;

    if(animating)
    {
        qDebug() << "animaing";

        if(m_webcamFrame)
        {
            delete m_webcamFrame;
            m_webcamFrame = nullptr;
        }

        if(m_webcamFrame_1)
        {
            delete m_webcamFrame_1;
            m_webcamFrame_1 = nullptr;
        }

        if(m_webcamFrame_2)
        {
            delete m_webcamFrame_2;
            m_webcamFrame_2 = nullptr;
        }

        if(m_webcamFrame_3)
        {
            delete m_webcamFrame_3;
            m_webcamFrame_3 = nullptr;
        }
    }
    else
    {
        qDebug() << "finished animaing";

        //get the aspect ratio for 16:9
        QSize size;
        qreal ratio = ((qreal)9/16);

        size.setWidth(width() - 10);
        size.setHeight(((int)((width() - 10) * ratio)));

        if(!m_webcamFrame && !m_webcamUrl.isEmpty())
        {
            qDebug() << QString("--setting stream url ") + m_webcamUrl;

            m_webcamFrame = new QWebcamWidget(m_webcamUrl, this);
            m_webcamFrame->resize(size);
            m_layout->addWidget(m_webcamFrame, 0, 0, 1, 1, Qt::AlignCenter);
            m_webcamFrame->play();
        }

        //resize for other frames (1/3)
        size.setWidth((width() -12) / 3);
        size.setHeight(((width() -12) / 3) * ratio);

        if(!m_webcamFrame_1 && !m_webcamUrl_1.isEmpty())
        {
            m_webcamFrame_1 = new QWebcamWidget(m_webcamUrl_1, this);
            m_layout->addWidget(m_webcamFrame_1, 1, 0, 1, 1, Qt::AlignCenter);
            m_webcamFrame_1->resize(size);
            m_webcamFrame_1->play();
        }

        if(!m_webcamFrame_2 && !m_webcamUrl_2.isEmpty())
        {
            m_webcamFrame_2 = new QWebcamWidget(m_webcamUrl_2, this);
            m_layout->addWidget(m_webcamFrame_2, 1, 1, 1, 1, Qt::AlignCenter);
            m_webcamFrame_2->resize(size);
            m_webcamFrame_2->play();
        }

        if(!m_webcamFrame_3 && !m_webcamUrl_3.isEmpty())
        {
            m_webcamFrame_3 = new QWebcamWidget(m_webcamUrl_3, this);
            m_layout->addWidget(m_webcamFrame_3, 1, 2, 1, 1, Qt::AlignCenter);
            m_webcamFrame_3->resize(size);
            m_webcamFrame_3->play();
        }
    }

    emit animatingChanged(animating);
}
