#include "printjobwidget.h"
#include "ui_printjobwidget.h"

#include "../../system/settings.h"
#include "../../system/printerpool.h"

PrintJobWidget::PrintJobWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::PrintJobWidget)
{
    ui->setupUi(this);
    _printJobList = new PrintJobListWidget();
    QGridLayout *layout = (QGridLayout*)ui->jobStatusTab->layout();
    layout->addWidget(_printJobList,1,0,1,2);

    connect(PrinterPool::instance(), SIGNAL(jobStarted(PrintJob*)), this, SLOT(on_printerPool_jobStarted(PrintJob*)));
    connect(PrinterPool::instance(), SIGNAL(jobFinished(PrintJob*)), this, SLOT(on_printerPool_jobFinished(PrintJob*)));
    connect(PrinterPool::instance(), SIGNAL(jobUpdated(PrintJob*)), this, SLOT(on_printerPool_jobUpdated(PrintJob*)));
}

PrintJobWidget::~PrintJobWidget()
{
    delete ui;
}

void PrintJobWidget::setUiClasses()
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "ListWidget" << "JobListWidget"));
}

void PrintJobWidget::loadPrintJobs()
{
    QList<PrintJob*> jobs = PrinterPool::printJobs();

    if(jobs.isEmpty())
    {
        PrintJob *job = new PrintJob();
        job->fileName = QString("No Jobs Running");
        job->printerName = QString("None");
        _printJobList->addJob(job);
    }
    else
    {
        foreach(PrintJob *job, jobs)
        {
            _printJobList->addJob(job);
        }
    }
}

void PrintJobWidget::setStyleSheet(QString styleSheet)
{
    QTabWidget::setStyleSheet(styleSheet);
    setTabIcon(2, Settings::getThemeIcon(QString("error-icon")));
    setTabIcon(1, Settings::getThemeIcon(QString("voltage-icon")));
    setTabIcon(0, Settings::getThemeIcon(QString("list-icon")));
}

void PrintJobWidget::on_printerPool_jobStarted(PrintJob *job)
{

}

void PrintJobWidget::on_printerPool_jobFinished(PrintJob *job)
{

}

void PrintJobWidget::on_printerPool_jobUpdated(PrintJob *job)
{

}
