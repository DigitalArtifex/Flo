#ifndef PRINTJOBITEM_H
#define PRINTJOBITEM_H

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
#include "ui/list/qanimatedlistitem.h"

class PrintJobItem : public QAnimatedListItem
{
    Q_OBJECT

public:
    explicit PrintJobItem(QWidget *parent = nullptr);
    ~PrintJobItem();


    QKlipperPrintJob *printJob();
    void setPrintJob(QKlipperPrintJob *job);

signals:
    void removeRequest(PrintJobItem *item);

protected slots:
    void setupUi();
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

Q_DECLARE_METATYPE(PrintJobItem)

#endif // PRINTJOBITEM_H
