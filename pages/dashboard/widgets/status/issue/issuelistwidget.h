#ifndef ISSUELISTWIDGET_H
#define ISSUELISTWIDGET_H

#include <QObject>
#include <QWidget>

#include <QKlipper/qklipper.h>
#include "system/qklipperinstancepool.h"
#include "../../../../../ui/list/qanimatedlistwidget.h"

#include "issuelistitem.h"

class IssueListWidget : public QAnimatedListWidget
{
    Q_OBJECT
public:
    IssueListWidget(QWidget *parent = nullptr);

    void addIssue(QString source, QKlipperError &error);

private slots:
    void onInstanceError(QKlipperInstance *instance, QKlipperError &error);
    void itemRemoveRequestEvent(IssueListItem *item);

private:
};

#endif // ISSUELISTWIDGET_H
