#include "printjoblistwidget.h"

PrintJobListWidget::PrintJobListWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{
    if(parent)
        setStyleSheet(parent->styleSheet());
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
    item->setPositionIn(item->pos());
    item->setPositionOut(QPoint(width(),item->pos().y()));
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(1000);

    addItem(item);
}

void PrintJobListWidget::removeJob(PrintJob *job)
{

}

void PrintJobListWidget::updateJob(PrintJob *job)
{

}
