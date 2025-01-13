#include "statuswidget.h"

#include "../../../../system/settings.h"
#include <system/qklipperinstancepool.h>

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
    // if(m_printJobList)
    //     m_printJobList->deleteLater();

    if(m_issueList)
        m_issueList->deleteLater();

    if(m_energyConsumption)
        m_energyConsumption->deleteLater();
}

void StatusWidget::setUiClasses()
{
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "JobWidget"));
}

void StatusWidget::loadPrintJobs()
{
    // QList<QKlipperPrintJob*> jobs = QKlipperInstancePool::printJobs();

    // foreach(QKlipperPrintJob *job, jobs)
    // {
    //     m_printJobList->addJob(job);
    // }

    connect(QKlipperInstancePool::pool(), SIGNAL(printJobAdded(QKlipperInstance*,QKlipperPrintJob*)), this, SLOT(onPrintJobAdded(QKlipperInstance*,QKlipperPrintJob*)));
    connect(QKlipperInstancePool::pool(), SIGNAL(printJobRemoved(QKlipperInstance*,QKlipperPrintJob*)), this, SLOT(onPrintJobRemoved(QKlipperInstance*,QKlipperPrintJob*)));
}

void StatusWidget::setStyleSheet(QString styleSheet)
{
    QTabWidget::setStyleSheet(styleSheet);
    setTabIcon(2, Settings::getThemeIcon(QString("error")));
    setTabIcon(1, Settings::getThemeIcon(QString("voltage")));
    setTabIcon(0, Settings::getThemeIcon(QString("list")));

    // m_printJobList->setStyleSheet(styleSheet);
}

void StatusWidget::onPrintJobAdded(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    Q_UNUSED(instance)

    // m_printJobList->addJob(job);
}

void StatusWidget::onPrintJobRemoved(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    Q_UNUSED(instance)

    // m_printJobList->removeJob(job);
}

void StatusWidget::setupJobPage()
{
    // m_printJobList = new PrintJobOverviewWidget(this);

    // addTab(m_printJobList, Settings::getThemeIcon(QString("list")), QString("Jobs"));

    // connect(PrinterPool::instance(), SIGNAL(printJobStarted(PrintJob*)), this, SLOT(on_printerPool_jobStarted(PrintJob*)));
    // connect(PrinterPool::instance(), SIGNAL(printJobFinished(PrintJob*)), this, SLOT(on_printerPool_jobFinished(PrintJob*)));
}

void StatusWidget::setupEnergyPage()
{
    m_energyConsumption = new EnergyConsumptionWidget;
    addTab(m_energyConsumption, Settings::getThemeIcon(QString("voltage")), QString("Energy Consumption"));
}

void StatusWidget::setupIssuesPage()
{
    m_issueList = new IssueListWidget(this);
    addTab(m_issueList, Settings::getThemeIcon(QString("error")), QString("Issues"));
}
