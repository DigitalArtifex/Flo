#include "printjobwidget.h"

PrintJobWidget::PrintJobWidget(QKlipperInstance *instance, QWidget *parent) :
    QAnimatedListWidget(parent)
{
    setEmptyText(QString("No Print Jobs Running"));

    connect(instance->server()->jobQueue(), SIGNAL(jobAdded(QKlipperPrintJob*)), this, SLOT(addJob(QKlipperPrintJob*)));
    connect(instance->server()->jobQueue(), SIGNAL(jobRemoved(QKlipperPrintJob*)), this, SLOT(removeJob(QKlipperPrintJob*)));
    //connect(QKlipperInstancePool::pool(), SIGNAL(printJobRemoved(QKlipperInstance*,QKlipperPrintJob*)), this, SLOT(onPrintJobRemoved(QKlipperInstance*,QKlipperPrintJob*)));
}

PrintJobWidget::~PrintJobWidget()
{

}

void PrintJobWidget::addJob(QKlipperPrintJob *job)
{
    for(QAnimatedListItem *item : m_items)
    {
        PrintJobItem *jobItem = qobject_cast<PrintJobItem*>(item);

        if(jobItem && jobItem->printJob()->id() == job->id())
            return;
    }

    PrintJobItem *item = new PrintJobItem(this);
    item->setPrintJob(job);

    connect(item, SIGNAL(removeRequest(PrintJobItem*)), this, SLOT(itemRemoveRequestEvent(PrintJobItem*)));

    addItem(item);
}

void PrintJobWidget::removeJob(QKlipperPrintJob *job)
{
    foreach(QAnimatedListItem *item, m_items)
    {
        PrintJobItem *jobItem = qobject_cast<PrintJobItem*>(item);

        if(jobItem && jobItem->printJob()->id() == job->id())
        {
            removeItem(item);
            break;
        }
    }
}

void PrintJobWidget::setupIcons()
{

}

void PrintJobWidget::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setupIcons();

    QAnimatedListWidget::changeEvent(event);
}

void PrintJobWidget::itemRemoveRequestEvent(PrintJobItem *item)
{
    removeItem(item);
}
