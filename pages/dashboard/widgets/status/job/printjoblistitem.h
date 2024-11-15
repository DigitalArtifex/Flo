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

#include <QKlipper/qklipper.h>
#include "../../../../../ui/list/qanimatedlistitem.h"

class PrintJobListItem : public QAnimatedListItem
{
    Q_OBJECT

public:
    explicit PrintJobListItem(QWidget *parent = nullptr);
    ~PrintJobListItem();

    void setupUi();

    QKlipperPrintJob *printJob();
    void setPrintJob(QKlipperPrintJob *job);

    virtual void setStyleSheet(const QString &styleSheet);

signals:
    void removeRequest(PrintJobListItem *item);

protected slots:
    void onPrintJobStateChanged();
    void onPrintJobCurrentLayerChanged();
    void onPrintJobTotalLayersChanged();
    void onInstanceNameChanged();

    void closeButtonClickEvent();
    void autoRemoveTimerTimeoutEvent();

private:
    QKlipperPrintJob *m_job;

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
