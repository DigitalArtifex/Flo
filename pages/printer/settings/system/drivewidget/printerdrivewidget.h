#ifndef PRINTERDRIVEWIDGET_H
#define PRINTERDRIVEWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QGroupBox>

#include "ui/common/cardwidget/cardwidget.h"
#include "ui/circularprogressbar.h"

#include "types/system.h"

class PrinterDriveWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterDriveWidget(System *system, QWidget *parent = nullptr);

signals:

protected slots:
    void setupUi();
    void systemMCUChanged();

    void convertDriveBytes(qreal &bytes, QString &label);
    void convertBytes(qreal &bytes, QString &label);

private:
    System *m_system = nullptr;

    System::SdInfo m_sdInfo;
    System::VirtualSDCard m_virtualSd;

    System::MCU m_mcu;

    QHBoxLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_progressLayout = nullptr;
    QVBoxLayout *m_sdLayout = nullptr;

    QGroupBox *m_sdGroupBox = nullptr;

    CircularProgressBar *m_mcuAverageProgressBar = nullptr;

    QLabel *m_frequencyLabel = nullptr;
    QLabel *m_hardwareLabel = nullptr;
    QLabel *m_firmwareLabel = nullptr;
    QLabel *m_wakeTimeLabel = nullptr;

    QWidget *m_centralWidget = nullptr;
    QWidget *m_progressWidget = nullptr;
};

#endif // PRINTERDRIVEWIDGET_H
