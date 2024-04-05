#ifndef PRINTJOBLISTITEM_H
#define PRINTJOBLISTITEM_H

#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QProgressBar>
#include <QGridLayout>
#include <QStringList>

#include "../../../types/printjob.h"
#include "../../list/qanimatedlistitem.h"

class PrintJobListItem : public QAnimatedListItem
{
    Q_OBJECT

public:
    explicit PrintJobListItem(QWidget *parent = nullptr);
    ~PrintJobListItem();

    void setupUi();

    PrintJob *printJob();
    void setPrintJob(PrintJob *job);
private:
    PrintJob *_job;
    QLabel *_jobNameLabel = nullptr;
    QLabel *_printerNameLabel = nullptr;
    QLabel *_timeRemainingLabel = nullptr;
    QLabel *_timeRunningLabel = nullptr;
    QLabel *_iconLabel = nullptr;
    QWidget *_iconContainer = nullptr;
    QProgressBar *_progressBar = nullptr;
};

#endif // PRINTJOBLISTITEM_H
