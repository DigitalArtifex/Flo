#ifndef ISSUELISTITEM_H
#define ISSUELISTITEM_H

#include <QObject>

#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QProgressBar>
#include <QGridLayout>
#include <QStringList>
#include <QSpacerItem>
#include <QToolButton>

#include "../../../../../types/printjob.h"
#include "../../../../../ui/list/qanimatedlistitem.h"

class IssueListItem : public QAnimatedListItem
{
    Q_OBJECT

public:
    explicit IssueListItem(QString title, QString source, QString message, QWidget *parent = nullptr);
    ~IssueListItem();

    void setupUi();

signals:
    void removeRequest(IssueListItem *item);

protected slots:
    void on_closeButton_clicked();

private:
    PrintJob *_job;

    QLabel *_titleLabel = nullptr;
    QLabel *_sourceLabel = nullptr;
    QLabel *_messageLabel = nullptr;
    QLabel *_iconLabel = nullptr;

    QSpacerItem *_spacer = nullptr;
    QSpacerItem *_buttonSpacer = nullptr;

    QToolButton *_closeButton = nullptr;

    QFrame *_separator;
    QWidget *_iconContainer = nullptr;
};

#endif // ISSUELISTITEM_H
