#include "issuelistwidget.h"

IssueListWidget::IssueListWidget(QWidget *parent) :
    QAnimatedListWidget(parent)
{
    connect(QKlipperInstancePool::pool(), SIGNAL(error(QKlipperInstance*,QKlipperError&)), this, SLOT(onInstanceError(QKlipperInstance*,QKlipperError&)));
    setEmptyText(QString("No Issues Found"));
}

void IssueListWidget::addIssue(QString source, QKlipperError &error)
{
    IssueListItem *item = new IssueListItem(error.errorTitle(), source, error.errorString(), this);
    connect(item, SIGNAL(removeRequest(IssueListItem*)), this, SLOT(itemRemoveRequestEvent(IssueListItem*)));

    addItem(item);
}

void IssueListWidget::onInstanceError(QKlipperInstance *instance, QKlipperError &error)
{
    addIssue(QString("Printer: ") + instance->name(), error);
}

void IssueListWidget::itemRemoveRequestEvent(IssueListItem *item)
{
    removeItem(item);
}
