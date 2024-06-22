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
    PrintJob *m_job;

    QLabel *m_titleLabel = nullptr;
    QLabel *m_sourceLabel = nullptr;
    QLabel *m_messageLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QSpacerItem *m_spacer = nullptr;
    QSpacerItem *m_buttonSpacer = nullptr;

    QToolButton *m_closeButton = nullptr;

    QFrame *m_separator;
    QWidget *m_iconContainer = nullptr;
};

#endif // ISSUELISTITEM_H
