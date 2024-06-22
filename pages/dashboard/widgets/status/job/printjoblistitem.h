#ifndef PRINTJOBLISTITEM_H
#define PRINTJOBLISTITEM_H

#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QProgressBar>
#include <QGridLayout>
#include <QStringList>

#include "../../../../../types/printjob.h"
#include "../../../../../types/printer.h"
#include "../../../../../ui/list/qanimatedlistitem.h"

class PrintJobListItem : public QAnimatedListItem
{
    Q_OBJECT

public:
    explicit PrintJobListItem(QWidget *parent = nullptr);
    ~PrintJobListItem();

    void setupUi();

    PrintJob *printJob();
    void setPrintJob(PrintJob *job);

    virtual void setStyleSheet(const QString &styleSheet);

signals:
    void removeRequested(PrintJobListItem *item);

protected slots:
    void on_printJob_finished(PrintJob *printJob);
    void on_printJob_paused(PrintJob *printJob);
    void on_printJob_resumed(PrintJob *printJob);
    void on_printJob_cancelled(PrintJob *printJob);
    void on_printJob_error(PrintJob *printJob);
    void on_printJob_updated(PrintJob *printJob);

private:
    PrintJob *m_job;
    QLabel *m_jobNameLabel = nullptr;
    QLabel *m_printerNameLabel = nullptr;
    QLabel *m_timeRemainingLabel = nullptr;
    QLabel *m_timeRunningLabel = nullptr;
    QLabel *m_iconLabel = nullptr;
    QWidget *m_iconContainer = nullptr;
    QProgressBar *m_progressBar = nullptr;
};

#endif // PRINTJOBLISTITEM_H
