#ifndef ISSUELISTWIDGET_H
#define ISSUELISTWIDGET_H

#include <QObject>
#include <QWidget>

#include "../../../../../types/printer.h"
#include "../../../../../system/printerpool.h"
#include "../../../../../ui/list/qanimatedlistwidget.h"

#include "issuelistitem.h"

class IssueListWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    IssueListWidget(QWidget *parent = nullptr);

    void addIssue(QString title, QString source, QString message);

private slots:
    void on_printerPool_printerError(QString title, QString message, Printer *printer);

private:
};

#endif // ISSUELISTWIDGET_H
