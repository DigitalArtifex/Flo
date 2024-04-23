#include "issuelistwidget.h"

IssueListWidget::IssueListWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{
    connect(PrinterPool::instance(), SIGNAL(printerError(QString,QString,Printer*)), this, SLOT(on_printerPool_printerError(QString,QString,Printer*)));
}

void IssueListWidget::addIssue(QString title, QString source, QString message)
{
    IssueListItem *item = new IssueListItem(title, source, message, this);
    item->setPositionIn(item->pos());
    item->setPositionOut(QPoint(width(),item->pos().y()));
    item->setOpacityIn(1);
    item->setOpacityOut(0);
    item->setDuration(1000);

    addItem(item);
}

void IssueListWidget::on_printerPool_printerError(QString title, QString message, Printer *printer)
{
    addIssue(title, QString("Printer: ") + printer->name(), message);
}
