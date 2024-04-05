#include "printjoblistitem.h"

PrintJobListItem::PrintJobListItem(QWidget *parent) :
    QAnimatedListItem(parent)
{
    setupUi();

    if(parent)
        setStyleSheet(parent->styleSheet());
}

PrintJobListItem::~PrintJobListItem()
{
    delete _iconLabel;
    delete _iconContainer;
    delete _jobNameLabel;
    delete _printerNameLabel;
    delete _timeRemainingLabel;
    delete _timeRunningLabel;
    delete _progressBar;
}

void PrintJobListItem::setupUi()
{
    QGridLayout *layout = new QGridLayout();

    _iconContainer = new QWidget(this);
    _iconContainer->setLayout(new QVBoxLayout(_iconContainer));
    _iconContainer->setBaseSize(100,100);
    _iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    layout->addWidget(_iconContainer,0,0,3,1);

    _iconLabel = new QLabel(this);
    _iconLabel->setBaseSize(100,100);
    _iconLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    _iconLabel->setAlignment(Qt::AlignCenter);
    _iconLabel->setText(QString("Icon"));
    _iconContainer->layout()->addWidget(_iconLabel);

    _jobNameLabel = new QLabel(this);
    _jobNameLabel->setText(QString("Name"));
    layout->addWidget(_jobNameLabel,0,1,1,2);

    _printerNameLabel = new QLabel(this);
    _printerNameLabel->setText(QString("Printer"));
    layout->addWidget(_printerNameLabel,1,1,1,2);

    _timeRemainingLabel = new QLabel(this);
    _timeRemainingLabel->setText(QString("Time Remaining"));
    layout->addWidget(_timeRemainingLabel,2,1,1,1);

    _timeRunningLabel = new QLabel(this);
    _timeRunningLabel->setText(QString("Time Running"));
    layout->addWidget(_timeRunningLabel,2,2,1,1);

    _progressBar = new QProgressBar(this);
    _progressBar->setMaximum(100);
    _progressBar->setMinimum(0);
    _progressBar->setValue(0);
    _progressBar->setTextVisible(false);
    layout->addWidget(_progressBar,3,0,1,3);

    setLayout(layout);
}

PrintJob *PrintJobListItem::printJob()
{
    return _job;
}

void PrintJobListItem::setPrintJob(PrintJob *job)
{
    _job = job;
    _jobNameLabel->setText(job->fileName);
    _printerNameLabel->setText(job->printerName);
    _timeRemainingLabel->setText(QString("Time Remaining: ") + job->endDate);
}
