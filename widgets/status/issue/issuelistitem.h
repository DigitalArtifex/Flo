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

#include "../../../types/printjob.h"
#include "../../list/qanimatedlistitem.h"

class IssueListItem : public QAnimatedListItem
{
    Q_OBJECT

public:
    explicit IssueListItem(QString title, QString source, QString message, QWidget *parent = nullptr);
    ~IssueListItem();

    void setupUi();
private:
    PrintJob *_job;

    QLabel *_titleLabel = nullptr;
    QLabel *_sourceLabel = nullptr;
    QLabel *_messageLabel = nullptr;
    QLabel *_iconLabel = nullptr;

    QWidget *_iconContainer = nullptr;
};

#endif // ISSUELISTITEM_H
