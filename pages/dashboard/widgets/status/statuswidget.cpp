#include "statuswidget.h"

#include "../../../../system/settings.h"
#include "../../../../system/printerpool.h"

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
    if(m_printJobList)
        delete m_printJobList;

    if(m_issueList)
        delete m_issueList;

    if(m_energyConsumption)
        delete m_energyConsumption;
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
        /*PrintJob *job = new PrintJob();
        job->fileName = QString("No Jobs Running");
        job->printerName = QString("None");
        m_printJobList->addJob(job);*/
    }
    else
    {
        foreach(PrintJob *job, jobs)
        {
            m_printJobList->addJob(job);
        }
    }
}

void StatusWidget::setStyleSheet(QString styleSheet)
{
    QTabWidget::setStyleSheet(styleSheet);
    setTabIcon(2, Settings::getThemeIcon(QString("error-icon")));
    setTabIcon(1, Settings::getThemeIcon(QString("voltage-icon")));
    setTabIcon(0, Settings::getThemeIcon(QString("list-icon")));

    m_printJobList->setStyleSheet(styleSheet);
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
    m_printJobList = new PrintJobListWidget(this);

    addTab(m_printJobList, Settings::getThemeIcon(QString("list-icon")), QString("Jobs"));

    connect(PrinterPool::instance(), SIGNAL(printJobStarted(PrintJob*)), this, SLOT(on_printerPool_jobStarted(PrintJob*)));
    connect(PrinterPool::instance(), SIGNAL(printJobFinished(PrintJob*)), this, SLOT(on_printerPool_jobFinished(PrintJob*)));
}

void StatusWidget::setupEnergyPage()
{
    m_energyConsumption = new EnergyConsumptionWidget;
    addTab(m_energyConsumption, Settings::getThemeIcon(QString("voltage-icon")), QString("Energy Consumption"));
}

void StatusWidget::setupIssuesPage()
{
    m_issueList = new IssueListWidget(this);
    addTab(m_issueList, Settings::getThemeIcon(QString("error-icon")), QString("Issues"));
}
