#include "printjoblistwidget.h"
#include "system/qklipperinstancepool.h"

PrintJobListWidget::PrintJobListWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{
    if(parent)
        setStyleSheet(parent->styleSheet());

    setEmptyText(QString("No Print Jobs Running"));

    connect(QKlipperInstancePool::pool(), SIGNAL(printJobAdded(QKlipperInstance*,QKlipperPrintJob*)), this, SLOT(onPrintJobAdded(QKlipperInstance*,QKlipperPrintJob*)));
    connect(QKlipperInstancePool::pool(), SIGNAL(printJobRemoved(QKlipperInstance*,QKlipperPrintJob*)), this, SLOT(onPrintJobRemoved(QKlipperInstance*,QKlipperPrintJob*)));
}

PrintJobListWidget::~PrintJobListWidget()
{
}

void PrintJobListWidget::setStyleSheet(QString styleSheet)
{
    QWidget::setStyleSheet(styleSheet);
}

void PrintJobListWidget::addJob(QKlipperPrintJob *job)
{
    bool found = false;

    foreach(QAnimatedListItem *item, m_items)
    {
        PrintJobListItem *jobItem = qobject_cast<PrintJobListItem*>(item);

        if(jobItem && jobItem->printJob()->id() == job->id())
        {
            found = true;
            break;
        }
    }

    if(!found)
    {
        PrintJobListItem *item = new PrintJobListItem(this);
        item->setPrintJob(job);
        setAnimationSlide(item);
        item->setOpacityIn(1);
        item->setOpacityOut(0);
        item->setDuration(250);

        connect(item, SIGNAL(removeRequest(PrintJobListItem*)), this, SLOT(itemRemoveRequestEvent(PrintJobListItem*)));

        addItem(item);
    }
}

void PrintJobListWidget::removeJob(QKlipperPrintJob *job)
{
    foreach(QAnimatedListItem *item, m_items)
    {
        PrintJobListItem *jobItem = qobject_cast<PrintJobListItem*>(item);

        if(jobItem && jobItem->printJob()->id() == job->id())
        {
            removeItem(item);
            break;
        }
    }
}

void PrintJobListWidget::onPrintJobAdded(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    Q_UNUSED(instance);
    addJob(job);
}

void PrintJobListWidget::onPrintJobRemoved(QKlipperInstance *instance, QKlipperPrintJob *job)
{
    Q_UNUSED(instance);
    addJob(job);
}

void PrintJobListWidget::itemRemoveRequestEvent(PrintJobListItem *item)
{
    removeItem(item);
}
