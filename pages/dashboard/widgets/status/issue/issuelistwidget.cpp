#include "issuelistwidget.h"

IssueListWidget::IssueListWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{
    connect(PrinterPool::instance(), SIGNAL(printerError(QString,QString,Printer*)), this, SLOT(on_printerPool_printerError(QString,QString,Printer*)));
    setEmptyText(QString("No Issues Found"));
}

void IssueListWidget::addIssue(QString title, QString source, QString message)
{
    IssueListItem *item = new IssueListItem(title, source, message, this);
    setAnimationSlide(item);
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(150);

    connect(item, SIGNAL(removeRequest(IssueListItem*)), this, SLOT(on_item_removeRequest(IssueListItem*)));

    addItem(item);
}

void IssueListWidget::on_printerPool_printerError(QString title, QString message, Printer *printer)
{
    addIssue(title, QString("Printer: ") + printer->name(), message);
}

void IssueListWidget::on_item_removeRequest(IssueListItem *item)
{
    removeItem(item);
}
