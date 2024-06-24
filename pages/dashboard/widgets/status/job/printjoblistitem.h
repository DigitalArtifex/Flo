#ifndef PRINTJOBLISTITEM_H
#define PRINTJOBLISTITEM_H

#include <QFrame>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QProgressBar>
#include <QGridLayout>
#include <QStringList>
#include <QToolButton>
#include <QTimer>

#include "../../../../../types/printjob.h"
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
    void removeRequest(PrintJobListItem *item);

protected slots:
    void on_printJob_finished(PrintJob *printJob);
    void on_printJob_paused(PrintJob *printJob);
    void on_printJob_resumed(PrintJob *printJob);
    void on_printJob_cancelled(PrintJob *printJob);
    void on_printJob_error(PrintJob *printJob);
    void on_printJob_updated(PrintJob *printJob);

    void closeButtonClickEvent();
    void autoRemoveTimerTimeoutEvent();

private:
    PrintJob *m_job;
    QLabel *m_jobNameLabel = nullptr;
    QLabel *m_printerNameLabel = nullptr;
    QLabel *m_timeRemainingLabel = nullptr;
    QLabel *m_timeRunningLabel = nullptr;
    QLabel *m_iconLabel = nullptr;
    QWidget *m_iconContainer = nullptr;
    QProgressBar *m_progressBar = nullptr;

    QToolButton *m_closeButton = nullptr;
    QTimer *m_autoRemoveTimer = nullptr;
};

#endif // PRINTJOBLISTITEM_H
