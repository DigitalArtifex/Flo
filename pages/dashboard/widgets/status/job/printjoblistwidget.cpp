#include "printjoblistwidget.h"
#include "../../../../../system/printerpool.h"

PrintJobListWidget::PrintJobListWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{
    if(parent)
        setStyleSheet(parent->styleSheet());

    setEmptyText(QString("No Print Jobs Running"));

    connect(PrinterPool::instance(), SIGNAL(printJobStarted(PrintJob*)), this, SLOT(on_printJob_started(PrintJob*)));
}

PrintJobListWidget::~PrintJobListWidget()
{
}

void PrintJobListWidget::setStyleSheet(QString styleSheet)
{
    QWidget::setStyleSheet(styleSheet);
}

void PrintJobListWidget::addJob(PrintJob *job)
{
    PrintJobListItem *item = new PrintJobListItem(this);
    item->setPrintJob(job);
    setAnimationSlide(item);
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(250);

    addItem(item);
}

void PrintJobListWidget::removeJob(PrintJob *job)
{

}

void PrintJobListWidget::updateJob(PrintJob *job)
{

}

void PrintJobListWidget::on_printJob_started(PrintJob *printJob)
{
    addJob(printJob);
}
