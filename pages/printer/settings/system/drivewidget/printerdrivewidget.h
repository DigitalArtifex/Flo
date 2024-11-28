#ifndef PRINTERDRIVEWIDGET_H
#define PRINTERDRIVEWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QGroupBox>

#include "ui/common/cardwidget/cardwidget.h"
#include "ui/circularprogressbar.h"

#include <QKlipper/qklipper.h>

class PrinterDriveWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterDriveWidget(QKlipperPrinter *printer, QWidget *parent = nullptr);

    virtual void setStyleSheet(const QString &styleSheet);

signals:

protected slots:
    void setupUi();
    void onPrinterMcuWakeTimeChanged();
    void onPrinterMcuFirmwareVersionChanged();
    void onPrinterMcuHardwareVersionChanged();
    void onPrinterMcuTaskAverageChanged();
    void onPrinterMcuFrequencyChanged();
    void onPrinterMcuChanged();

    void convertDriveBytes(qreal &bytes, QString &label);
    void convertBytes(qreal &bytes, QString &label);

private:
    QKlipperPrinter *m_printer = nullptr;

    QKlipperMCU *m_mcu;

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
