#include "printerwebcamwidget.h"

PrinterWebcamWidget::PrinterWebcamWidget(Printer *printer, QWidget *parent) :
    QFrame(parent)
{
    _printer = printer;

    setupUi();
    setupUiClasses();

    _delayTimer = new QTimer(this);
    _delayTimer->setSingleShot(true);
    _delayTimer->setInterval(2000);

    connect(_printer, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printer_update(Printer*)));
}

PrinterWebcamWidget::~PrinterWebcamWidget()
{
    if(_webcamFrame)
        delete _webcamFrame;

    if(_webcamFrame_1)
        delete _webcamFrame;

    if(_webcamFrame_2)
        delete _webcamFrame;

    if(_webcamFrame_3)
        delete _webcamFrame;

    if(_delayTimer)
        delete _delayTimer;

    if(_emptyFrame)
        delete _emptyFrame;

    if(_layout)
        delete _layout;
}

void PrinterWebcamWidget::setStyleSheet(QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    setIcons();

    style()->polish(this);
}

void PrinterWebcamWidget::setupUi()
{
    _layout = new QGridLayout(this);
    _layout->setContentsMargins(0,0,0,0);
    setLayout(_layout);

    //setup primary webcam

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(!_webcamFrame)
    {
        qDebug() << QString("--setting stream url ") + _webcamUrl;

        _webcamFrame = new QWebcamWidget(_webcamUrl, this);
        _webcamFrame->resize(size);
        _layout->addWidget(_webcamFrame, 0, 0, 1, 1, Qt::AlignCenter);
        _webcamFrame->play();
    }

    /*
    _webcamFrame_1 = new QWebcamWidget(this);
    _layout->addWidget(_webcamFrame_1, 1, 0);

    _webcamFrame_2 = new QWebcamWidget(this);
    _layout->addWidget(_webcamFrame_2, 1, 1);

    _webcamFrame_3 = new QWebcamWidget(this);
    _layout->addWidget(_webcamFrame_3, 1, 2);*/

    _emptyFrame = new EmptyPrinterWebcamFrame(this);
    _emptyFrame->setFixedSize(geometry().size());
    _emptyFrame->raise();
    _emptyFrame->setHidden(true);
}

void PrinterWebcamWidget::setupUiClasses()
{
}

void PrinterWebcamWidget::setIcons()
{

}

void PrinterWebcamWidget::setupWebcam0()
{
    _webcamFrame->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam1()
{
    _webcamFrame_1->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam2()
{
    _webcamFrame_2->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setupWebcam3()
{
    _webcamFrame_3->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::on_printer_update(Printer *printer)
{
    Q_UNUSED(printer);

    if(_printer->system()->webcams().count() > 0 && _webcamIndex == -1)
    {
        for(int i = 0; i < _printer->system()->webcams().count(); i++)
        {
            System::Webcam webcam = _printer->system()->webcams()[i];

            if(i == 0)
            {
                QString url = QString("http://") + _printer->system()->hostname() + webcam.streamUrl;

                _webcamUrl = url;

                if(_webcamFrame)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(_webcamFrame->source() != url)
                    {
                        _webcamFrame->stop();
                        _webcamFrame->setSource(url);
                        _webcamFrame->play();
                    }

                    _webcamFrame->setInfo(fps);
                    _webcamFrame->setTitle(webcam.name);
                }
            }

            else if(i == 1)
            {
                QString url = QString("http://") + _printer->system()->hostname() + webcam.streamUrl;

                _webcamUrl_1 = url;

                if(_webcamFrame_1)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(_webcamFrame_1->source() != url)
                    {
                        _webcamFrame_1->stop();
                        _webcamFrame_1->setSource(url);
                        _webcamFrame_1->play();
                    }

                    _webcamFrame_1->setInfo(fps);
                    _webcamFrame_1->setTitle(webcam.name);
                }
            }

            else if(i == 2)
            {
                QString url = QString("http://") + _printer->system()->hostname() + webcam.streamUrl;

                _webcamUrl_2 = url;

                if(_webcamFrame_2)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(_webcamFrame_2->source() != url)
                    {
                        _webcamFrame_2->stop();
                        _webcamFrame_2->setSource(url);
                        _webcamFrame_2->play();
                    }

                    _webcamFrame_2->setInfo(fps);
                    _webcamFrame_2->setTitle(webcam.name);
                }
            }

            else if(i == 3)
            {
                QString url = QString("http://") + _printer->system()->hostname() + webcam.streamUrl;

                _webcamUrl_3 = url;

                if(_webcamFrame_3)
                {
                    QString fps = QString::number(webcam.targetFps);

                    if(_webcamFrame_3->source() != url)
                    {
                        _webcamFrame_3->stop();
                        _webcamFrame_3->setSource(url);
                        _webcamFrame_3->play();
                    }

                    _webcamFrame_3->setInfo(fps);
                    _webcamFrame_3->setTitle(webcam.name);
                }
            }
        }

        _webcamIndex = 0;

        if(_emptyFrame)
        {
            _emptyFrame->lower();
            _emptyFrame->setHidden(true);
        }
    }
    else
    {
        if(_emptyFrame && !_emptyFrame->isHidden())
        {
            _emptyFrame->raise();
            _emptyFrame->setHidden(false);
        }
    }
}

void PrinterWebcamWidget::resizeEvent(QResizeEvent *event)
{
    if(_emptyFrame)
        _emptyFrame->resize(event->size());

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    if(_webcamFrame)
        _webcamFrame->resize(size);

    //resize for other frames (1/3)
    size.setWidth((width() -12) / 3);
    size.setHeight(((width() -12) / 3) * ratio);

    if(_webcamFrame_1)
        _webcamFrame_1->resize(size);

    if(_webcamFrame_2)
        _webcamFrame_2->resize(size);

    if(_webcamFrame_3)
        _webcamFrame_3->resize(size);
}

bool PrinterWebcamWidget::animating() const
{
    return _animating;
}

void PrinterWebcamWidget::setAnimating(bool animating)
{
    _animating = animating;

    if(animating)
    {
        qDebug() << "animaing";

        if(_webcamFrame)
        {
            delete _webcamFrame;
            _webcamFrame = nullptr;
        }

        if(_webcamFrame_1)
        {
            delete _webcamFrame_1;
            _webcamFrame_1 = nullptr;
        }

        if(_webcamFrame_2)
        {
            delete _webcamFrame_2;
            _webcamFrame_2 = nullptr;
        }

        if(_webcamFrame_3)
        {
            delete _webcamFrame_3;
            _webcamFrame_3 = nullptr;
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

        if(!_webcamFrame && !_webcamUrl.isEmpty())
        {
            qDebug() << QString("--setting stream url ") + _webcamUrl;

            _webcamFrame = new QWebcamWidget(_webcamUrl, this);
            _webcamFrame->resize(size);
            _layout->addWidget(_webcamFrame, 0, 0, 1, 1, Qt::AlignCenter);
            _webcamFrame->play();
        }

        //resize for other frames (1/3)
        size.setWidth((width() -12) / 3);
        size.setHeight(((width() -12) / 3) * ratio);

        if(!_webcamFrame_1 && !_webcamUrl_1.isEmpty())
        {
            _webcamFrame_1 = new QWebcamWidget(_webcamUrl_1, this);
            _layout->addWidget(_webcamFrame_1, 1, 0, 1, 1, Qt::AlignCenter);
            _webcamFrame_1->resize(size);
            _webcamFrame_1->play();
        }

        if(!_webcamFrame_2 && !_webcamUrl_2.isEmpty())
        {
            _webcamFrame_2 = new QWebcamWidget(_webcamUrl_2, this);
            _layout->addWidget(_webcamFrame_2, 1, 1, 1, 1, Qt::AlignCenter);
            _webcamFrame_2->resize(size);
            _webcamFrame_2->play();
        }

        if(!_webcamFrame_3 && !_webcamUrl_3.isEmpty())
        {
            _webcamFrame_3 = new QWebcamWidget(_webcamUrl_3, this);
            _layout->addWidget(_webcamFrame_3, 1, 2, 1, 1, Qt::AlignCenter);
            _webcamFrame_3->resize(size);
            _webcamFrame_3->play();
        }
    }

    emit animatingChanged(animating);
}
