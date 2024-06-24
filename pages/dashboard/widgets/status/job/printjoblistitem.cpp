#include "printjoblistitem.h"
#include "../../../../../system/settings.h"
#include "../../../../../types/printer.h"

PrintJobListItem::PrintJobListItem(QWidget *parent) :
    QAnimatedListItem(parent)
{
    setupUi();
}

PrintJobListItem::~PrintJobListItem()
{
    delete m_iconLabel;
    delete m_iconContainer;
    delete m_jobNameLabel;
    delete m_printerNameLabel;
    delete m_timeRemainingLabel;
    delete m_timeRunningLabel;
    delete m_progressBar;

    if(m_closeButton)
        delete m_closeButton;
}

void PrintJobListItem::setupUi()
{
    QGridLayout *layout = new QGridLayout();

    m_iconContainer = new QWidget(this);
    m_iconContainer->setLayout(new QVBoxLayout(m_iconContainer));
    m_iconContainer->setBaseSize(100,100);
    m_iconContainer->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum));
    layout->addWidget(m_iconContainer,0,0,3,1);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(32,32);
    m_iconLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setText(QString("Icon"));
    m_iconContainer->layout()->addWidget(m_iconLabel);

    m_jobNameLabel = new QLabel(this);
    m_jobNameLabel->setText(QString("Name"));
    layout->addWidget(m_jobNameLabel,0,1,1,2);

    m_closeButton = new QToolButton(this);
    m_closeButton->setIcon(Settings::getThemeIcon(QString("close-icon")));
    connect(m_closeButton, SIGNAL(clicked(bool)), this, SLOT(closeButtonClickEvent()));
    layout->addWidget(m_closeButton,0,3,1,1);

    m_printerNameLabel = new QLabel(this);
    m_printerNameLabel->setText(QString("Printer"));
    layout->addWidget(m_printerNameLabel,1,1,1,2);

    m_timeRemainingLabel = new QLabel(this);
    m_timeRemainingLabel->setText(QString("Time Remaining"));
    layout->addWidget(m_timeRemainingLabel,2,1,1,1);

    m_timeRunningLabel = new QLabel(this);
    m_timeRunningLabel->setText(QString("Time Running"));
    layout->addWidget(m_timeRunningLabel,2,2,1,2);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setMaximum(100);
    m_progressBar->setMinimum(0);
    m_progressBar->setValue(0);
    m_progressBar->setTextVisible(false);
    layout->addWidget(m_progressBar,3,0,1,3);

    setLayout(layout);
}

PrintJob *PrintJobListItem::printJob()
{
    return m_job;
}

void PrintJobListItem::setPrintJob(PrintJob *job)
{
    m_job = job;
    m_jobNameLabel->setText(job->filename());
    m_printerNameLabel->setText(job->parent()->name());

    QPixmap pixmap;

    switch (m_job->state())
    {
        case PrintJob::Standby:
            break;
        case PrintJob::Printing:
            pixmap = Settings::getThemeIcon(QString("printjob-printing-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Paused:
            pixmap = Settings::getThemeIcon(QString("printjob-paused-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Complete:
            pixmap = Settings::getThemeIcon(QString("printjob-completed-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Cancelled:
            pixmap = Settings::getThemeIcon(QString("printjob-cancelled-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;
        case PrintJob::Error:
            pixmap = Settings::getThemeIcon(QString("printjob-error-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;
    }

    //_timeRemainingLabel->setText(QString("Time Remaining: ") + job->endDate);

    connect(m_job, SIGNAL(finished(PrintJob*)), this, SLOT(on_printJob_finished(PrintJob*)));
    connect(m_job, SIGNAL(cancelled(PrintJob*)), this, SLOT(on_printJob_cancelled(PrintJob*)));
    connect(m_job, SIGNAL(error(PrintJob*)), this, SLOT(on_printJob_error(PrintJob*)));
    connect(m_job, SIGNAL(paused(PrintJob*)), this, SLOT(on_printJob_paused(PrintJob*)));
    connect(m_job, SIGNAL(resumed(PrintJob*)), this, SLOT(on_printJob_resumed(PrintJob*)));
    connect(m_job, SIGNAL(updated(PrintJob*)), this, SLOT(on_printJob_updated(PrintJob*)));
}

void PrintJobListItem::setStyleSheet(const QString &styleSheet)
{
    QFrame::setStyleSheet(styleSheet);

    QPixmap pixmap;

    switch (m_job->state())
    {
        case PrintJob::Standby:
            break;

        case PrintJob::Printing:
            pixmap = Settings::getThemeIcon(QString("printjob-printing-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Paused:
            pixmap = Settings::getThemeIcon(QString("printjob-paused-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Complete:
            pixmap = Settings::getThemeIcon(QString("printjob-completed-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Cancelled:
            pixmap = Settings::getThemeIcon(QString("printjob-cancelled-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
            break;

        case PrintJob::Error:
            pixmap = Settings::getThemeIcon(QString("printjob-error-icon")).pixmap(m_iconLabel->size());
            m_iconLabel->setPixmap(pixmap);
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
    QPixmap pixmap = Settings::getThemeIcon(QString("printjob-paused-icon")).pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);
}

void PrintJobListItem::on_printJob_resumed(PrintJob *printJob)
{
    QPixmap pixmap = Settings::getThemeIcon(QString("printjob-resume-icon")).pixmap(m_iconLabel->size());
    m_iconLabel->setPixmap(pixmap);
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

    switch (m_job->state())
    {
    case PrintJob::Standby:
        break;

    case PrintJob::Printing:
        pixmap = Settings::getThemeIcon(QString("printjob-printing-icon")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;

    case PrintJob::Paused:
        pixmap = Settings::getThemeIcon(QString("printjob-paused-icon")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;

    case PrintJob::Complete:
        pixmap = Settings::getThemeIcon(QString("printjob-completed-icon")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);

        if(!m_autoRemoveTimer)
        {
            m_autoRemoveTimer = new QTimer(this);
            m_autoRemoveTimer->setInterval(10000);
            connect(m_autoRemoveTimer, SIGNAL(timeout()), this, SLOT(autoRemoveTimerTimeoutEvent()));
            m_autoRemoveTimer->start();
        }
        break;

    case PrintJob::Cancelled:
        pixmap = Settings::getThemeIcon(QString("printjob-cancelled-icon")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);

        if(!m_autoRemoveTimer)
        {
            m_autoRemoveTimer = new QTimer(this);
            m_autoRemoveTimer->setInterval(10000);
            connect(m_autoRemoveTimer, SIGNAL(timeout()), this, SLOT(autoRemoveTimerTimeoutEvent()));
            m_autoRemoveTimer->start();
        }

        break;

    case PrintJob::Error:
        pixmap = Settings::getThemeIcon(QString("printjob-error-icon")).pixmap(m_iconLabel->size());
        m_iconLabel->setPixmap(pixmap);
        break;
    }

    m_timeRemainingLabel->setText(QString("Current Layer: ") + QString::number(m_job->currentLayer()));
    m_timeRunningLabel->setText(QString("Total Layers: ") + QString::number(m_job->totalLayers()));

    qreal progress = (qreal)m_job->currentLayer() / (qreal)m_job->totalLayers();
    progress *= 100;

    m_progressBar->setValue((int)progress);
}

void PrintJobListItem::closeButtonClickEvent()
{
    emit removeRequest(this);
}

void PrintJobListItem::autoRemoveTimerTimeoutEvent()
{
    if(m_autoRemoveTimer)
    {
        delete m_autoRemoveTimer;
        m_autoRemoveTimer = nullptr;
    }

    emit removeRequest(this);
}
