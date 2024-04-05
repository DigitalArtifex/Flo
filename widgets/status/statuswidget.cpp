#include "statuswidget.h"

#include "../../system/settings.h"
#include "../../system/printerpool.h"

StatusWidget::StatusWidget(QWidget *parent) :
    QTabWidget(parent)
{
    setupJobPage();
    setupEnergyPage();
    setupIssuesPage();

    loadPrintJobs();

    if(parent)
        setStyleSheet(parent->styleSheet());
}

StatusWidget::~StatusWidget()
{
}

void StatusWidget::setUiClasses()
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "JobWidget"));
}

void StatusWidget::loadPrintJobs()
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

void StatusWidget::setStyleSheet(QString styleSheet)
{
    QTabWidget::setStyleSheet(styleSheet);
    setTabIcon(2, Settings::getThemeIcon(QString("error-icon")));
    setTabIcon(1, Settings::getThemeIcon(QString("voltage-icon")));
    setTabIcon(0, Settings::getThemeIcon(QString("list-icon")));

    _printJobList->setStyleSheet(styleSheet);
}

void StatusWidget::on_printerPool_jobStarted(PrintJob *job)
{

}

void StatusWidget::on_printerPool_jobFinished(PrintJob *job)
{

}

void StatusWidget::on_printerPool_jobUpdated(PrintJob *job)
{

}

void StatusWidget::setupJobPage()
{
    _printJobList = new PrintJobListWidget(this);

    addTab(_printJobList, Settings::getThemeIcon(QString("list-icon")), QString("Jobs"));

    connect(PrinterPool::instance(), SIGNAL(jobStarted(PrintJob*)), this, SLOT(on_printerPool_jobStarted(PrintJob*)));
    connect(PrinterPool::instance(), SIGNAL(jobFinished(PrintJob*)), this, SLOT(on_printerPool_jobFinished(PrintJob*)));
    connect(PrinterPool::instance(), SIGNAL(jobUpdated(PrintJob*)), this, SLOT(on_printerPool_jobUpdated(PrintJob*)));
}

void StatusWidget::setupEnergyPage()
{
    _energyConsumption = new EnergyConsumptionWidget(this);
    addTab(_energyConsumption, Settings::getThemeIcon(QString("voltage-icon")), QString("Energy Consumption"));
}

void StatusWidget::setupIssuesPage()
{
    _issueList = new IssueListWidget(this);
    addTab(_issueList, Settings::getThemeIcon(QString("error-icon")), QString("Issues"));
}
