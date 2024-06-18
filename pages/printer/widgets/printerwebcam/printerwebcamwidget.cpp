#include "printerwebcamwidget.h"

PrinterWebcamWidget::PrinterWebcamWidget(Printer *printer, QWidget *parent) :
    QFrame(parent)
{
    _printer = printer;

    setupUi();
    setupUiClasses();

    connect(_printer, SIGNAL(printerUpdate(Printer*)), this, SLOT(on_printer_update(Printer*)));
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
    _webcamFrame = new QWebcamFrame(this);
    _layout->addWidget(_webcamFrame, 0, 0, 1, 3, Qt::AlignCenter);

    _webcamFrame_1 = new QWebcamFrame(this);
    _layout->addWidget(_webcamFrame_1, 1, 0);

    _webcamFrame_2 = new QWebcamFrame(this);
    _layout->addWidget(_webcamFrame_2, 1, 1);

    _webcamFrame_3 = new QWebcamFrame(this);
    _layout->addWidget(_webcamFrame_3, 1, 2);

    _emptyFrame = new EmptyPrinterWebcamFrame(this);
    _emptyFrame->setFixedSize(geometry().size());
    _emptyFrame->raise();
    _emptyFrame->setHidden(false);
}

void PrinterWebcamWidget::setupUiClasses()
{
    _webcamFrame->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
    _webcamFrame_1->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
    _webcamFrame_2->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
    _webcamFrame_3->setProperty("class", QVariant::fromValue<QStringList>(QStringList() << "SubWidget"));
}

void PrinterWebcamWidget::setIcons()
{

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
                QString fps = QString::number(webcam.targetFps);

                _webcamFrame->setSource(url);
                _webcamFrame->showInfo();
                _webcamFrame->setTitle(webcam.name);

                _webcamFrame->play();
            }

            else if(i == 1)
            {
                QString url = QString("http://") + _printer->system()->hostname() + webcam.streamUrl;

                _webcamFrame_1->setSource(url);
                _webcamFrame_1->play();
            }

            else if(i == 2)
            {
                QString url = QString("http://") + _printer->system()->hostname() + webcam.streamUrl;

                _webcamFrame_2->setSource(url);
                _webcamFrame_2->play();
            }

            else if(i == 3)
            {
                QString url = QString("http://") + _printer->system()->hostname() + webcam.streamUrl;

                _webcamFrame_3->setSource(url);
                _webcamFrame_3->play();
            }
        }

        _webcamIndex = 0;
        _emptyFrame->lower();
        _emptyFrame->setHidden(true);
    }
    else
    {
        if(!_emptyFrame->isHidden())
        {
            _emptyFrame->raise();
            _emptyFrame->setHidden(false);
        }
    }
}

void PrinterWebcamWidget::resizeEvent(QResizeEvent *event)
{
    if(_emptyFrame)
        _emptyFrame->setFixedSize(event->size());

    //get the aspect ratio for 16:9
    QSize size;
    qreal ratio = ((qreal)9/16);

    size.setWidth(width() - 10);
    size.setHeight(((int)((width() - 10) * ratio)));

    _webcamFrame->setFixedSize(size);

    //resize for other frames (1/3)
    size.setWidth((width() -12) / 3);
    size.setHeight(((width() -12) / 3) * ratio);

    _webcamFrame_1->setFixedSize(size);
    _webcamFrame_2->setFixedSize(size);
    _webcamFrame_3->setFixedSize(size);
}
