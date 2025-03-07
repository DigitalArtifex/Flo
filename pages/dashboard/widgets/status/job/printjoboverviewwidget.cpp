#include "printjoboverviewwidget.h"
#include "flo/qklipperinstancepool.h"

PrintJobOverviewWidget::PrintJobOverviewWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{
    if(parent)
        setStyleSheet(parent->styleSheet());

    setEmptyText(QString("No Print Jobs Running"));

    connect(QKlipperInstancePool::pool(), SIGNAL(printJobAdded(QKlipperInstance*,QKlipperPrintJob*)), this, SLOT(onPrintJobAdded(QKlipperInstance*,QKlipperPrintJob*)));
    connect(QKlipperInstancePool::pool(), SIGNAL(printJobRemoved(QKlipperInstance*,QKlipperPrintJob*)), this, SLOT(onPrintJobRemoved(QKlipperInstance*,QKlipperPrintJob*)));
}

PrintJobOverviewWidget::~PrintJobOverviewWidget()
{
}

void PrintJobOverviewWidget::setStyleSheet(QString styleSheet)
{
    QWidget::setStyleSheet(styleSheet);
}

void PrintJobOverviewWidget::addJob(QKlipperPrintJob *job)
{
    bool found = false;

    foreach(QAnimatedListItem *item, m_items)
    {
        PrintJobOverviewItem *jobItem = qobject_cast<PrintJobOverviewItem*>(item);

        if(jobItem && jobItem->printJob()->id() == job->id())
        {
            found = true;
            break;
        }
    }

    if(!found)
    {
        PrintJobOverviewItem *item = new PrintJobOverviewItem(this);
        item->setPrintJob(job);
        connect(item, SIGNAL(removeRequest(PrintJobOverviewItem*)), this, SLOT(itemRemoveRequestEvent(PrintJobOverviewItem*)));

        addItem(item);
    }
}

void PrintJobOverviewWidget::removeJob(QKlipperPrintJob *job)
{
    foreach(QAnimatedListItem *item, m_items)
    {
        PrintJobOverviewItem *jobItem = qobject_cast<PrintJobOverviewItem*>(item);

        if(jobItem && jobItem->printJob()->id() == job->id())
        {
            removeItem(item);
            break;
        }
    }
}

void PrintJobOverviewWidget::onPrintJobAdded(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    Q_UNUSED(instance);
    addJob(job);
}

void PrintJobOverviewWidget::onPrintJobRemoved(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    Q_UNUSED(instance);
    addJob(job);
}

void PrintJobOverviewWidget::itemRemoveRequestEvent(PrintJobOverviewItem *item)
{
    removeItem(item);
}
