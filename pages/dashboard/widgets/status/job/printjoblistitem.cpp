#include "printjoblistitem.h"
#include "../../../../../system/settings.h"

PrintJobListItem::PrintJobListItem(QWidget *parent) :
    QAnimatedListItem(parent)
{
    setupUi();
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
    _jobNameLabel->setText(job->filename());
    _printerNameLabel->setText(job->parent()->name());

    QPixmap pixmap;

    switch (_job->state())
    {
        case PrintJob::Standby:
            break;
        case PrintJob::Printing:
            pixmap = Settings::getThemeIcon(QString("printjob-printing-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Paused:
            pixmap = Settings::getThemeIcon(QString("printjob-paused-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Complete:
            pixmap = Settings::getThemeIcon(QString("printjob-completed-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Cancelled:
            pixmap = Settings::getThemeIcon(QString("printjob-cancelled-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Error:
            pixmap = Settings::getThemeIcon(QString("printjob-error-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;
    }

    //_timeRemainingLabel->setText(QString("Time Remaining: ") + job->endDate);

    connect(_job, SIGNAL(finished(PrintJob*)), this, SLOT(on_printJob_finished(PrintJob*)));
    connect(_job, SIGNAL(cancelled(PrintJob*)), this, SLOT(on_printJob_cancelled(PrintJob*)));
    connect(_job, SIGNAL(error(PrintJob*)), this, SLOT(on_printJob_error(PrintJob*)));
    connect(_job, SIGNAL(paused(PrintJob*)), this, SLOT(on_printJob_paused(PrintJob*)));
    connect(_job, SIGNAL(resumed(PrintJob*)), this, SLOT(on_printJob_resumed(PrintJob*)));
    connect(_job, SIGNAL(updated(PrintJob*)), this, SLOT(on_printJob_updated(PrintJob*)));
}

void PrintJobListItem::setStyleSheet(const QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    QPixmap pixmap;

    switch (_job->state())
    {
        case PrintJob::Standby:
            break;

        case PrintJob::Printing:
            pixmap = Settings::getThemeIcon(QString("printjob-printing-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Paused:
            pixmap = Settings::getThemeIcon(QString("printjob-paused-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Complete:
            pixmap = Settings::getThemeIcon(QString("printjob-completed-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Cancelled:
            pixmap = Settings::getThemeIcon(QString("printjob-cancelled-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Error:
            pixmap = Settings::getThemeIcon(QString("printjob-error-icon")).pixmap(_iconLabel->size());
            _iconLabel->setPixmap(pixmap);
            break;
    }
}

void PrintJobListItem::on_printJob_finished(PrintJob *printJob)
{
    disconnect(printJob, SIGNAL(finished(PrintJob*)), this, SLOT(on_printJob_finished(PrintJob*)));
    disconnect(printJob, SIGNAL(cancelled(PrintJob*)), this, SLOT(on_printJob_cancelled(PrintJob*)));
    disconnect(printJob, SIGNAL(error(PrintJob*)), this, SLOT(on_printJob_error(PrintJob*)));
    disconnect(printJob, SIGNAL(paused(PrintJob*)), this, SLOT(on_printJob_paused(PrintJob*)));
    disconnect(printJob, SIGNAL(resumed(PrintJob*)), this, SLOT(on_printJob_resumed(PrintJob*)));
    disconnect(printJob, SIGNAL(updated(PrintJob*)), this, SLOT(on_printJob_updated(PrintJob*)));
}

void PrintJobListItem::on_printJob_paused(PrintJob *printJob)
{

}

void PrintJobListItem::on_printJob_resumed(PrintJob *printJob)
{

}

void PrintJobListItem::on_printJob_cancelled(PrintJob *printJob)
{
    disconnect(printJob, SIGNAL(finished(PrintJob*)), this, SLOT(on_printJob_finished(PrintJob*)));
    disconnect(printJob, SIGNAL(cancelled(PrintJob*)), this, SLOT(on_printJob_cancelled(PrintJob*)));
    disconnect(printJob, SIGNAL(error(PrintJob*)), this, SLOT(on_printJob_error(PrintJob*)));
    disconnect(printJob, SIGNAL(paused(PrintJob*)), this, SLOT(on_printJob_paused(PrintJob*)));
    disconnect(printJob, SIGNAL(resumed(PrintJob*)), this, SLOT(on_printJob_resumed(PrintJob*)));
    disconnect(printJob, SIGNAL(updated(PrintJob*)), this, SLOT(on_printJob_updated(PrintJob*)));
}

void PrintJobListItem::on_printJob_error(PrintJob *printJob)
{

    disconnect(printJob, SIGNAL(finished(PrintJob*)), this, SLOT(on_printJob_finished(PrintJob*)));
    disconnect(printJob, SIGNAL(cancelled(PrintJob*)), this, SLOT(on_printJob_cancelled(PrintJob*)));
    disconnect(printJob, SIGNAL(error(PrintJob*)), this, SLOT(on_printJob_error(PrintJob*)));
    disconnect(printJob, SIGNAL(paused(PrintJob*)), this, SLOT(on_printJob_paused(PrintJob*)));
    disconnect(printJob, SIGNAL(resumed(PrintJob*)), this, SLOT(on_printJob_resumed(PrintJob*)));
    disconnect(printJob, SIGNAL(updated(PrintJob*)), this, SLOT(on_printJob_updated(PrintJob*)));
}

void PrintJobListItem::on_printJob_updated(PrintJob *printJob)
{
    QPixmap pixmap;

    switch (_job->state())
    {
    case PrintJob::Standby:
        break;

    case PrintJob::Printing:
        pixmap = Settings::getThemeIcon(QString("printjob-printing-icon")).pixmap(_iconLabel->size());
        _iconLabel->setPixmap(pixmap);
        break;

    case PrintJob::Paused:
        pixmap = Settings::getThemeIcon(QString("printjob-paused-icon")).pixmap(_iconLabel->size());
        _iconLabel->setPixmap(pixmap);
        break;

    case PrintJob::Complete:
        pixmap = Settings::getThemeIcon(QString("printjob-completed-icon")).pixmap(_iconLabel->size());
        _iconLabel->setPixmap(pixmap);
        break;

    case PrintJob::Cancelled:
        pixmap = Settings::getThemeIcon(QString("printjob-cancelled-icon")).pixmap(_iconLabel->size());
        _iconLabel->setPixmap(pixmap);
        break;

    case PrintJob::Error:
        pixmap = Settings::getThemeIcon(QString("printjob-error-icon")).pixmap(_iconLabel->size());
        _iconLabel->setPixmap(pixmap);
        break;
    }

    _timeRemainingLabel->setText(QString("Current Layer: ") + QString::number(_job->currentLayer()));
    _timeRunningLabel->setText(QString("Total Layers: ") + QString::number(_job->totalLayers()));

    qreal progress = (qreal)_job->currentLayer() / (qreal)_job->totalLayers();
    progress *= 100;

    _progressBar->setValue((int)progress);
}
