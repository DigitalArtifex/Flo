#ifndef PRINTJOBLISTITEM_H
#define PRINTJOBLISTITEM_H

#include <QFrame>

#include "../../types/printjob.h"

namespace Ui {
class PrintJobListItem;
}

class PrintJobListItem : public QFrame
{
    Q_OBJECT

public:
    explicit PrintJobListItem(QWidget *parent = nullptr);
    ~PrintJobListItem();

    void setUiClasses();

    PrintJob *printJob();

    virtual void setStyleSheet(QString styleSheet);
private:
    Ui::PrintJobListItem *ui;
    PrintJob *_job;
};

#endif // PRINTJOBLISTITEM_H
