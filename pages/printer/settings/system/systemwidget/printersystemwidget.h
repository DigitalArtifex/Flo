#ifndef PRINTERSYSTEMWIDGET_H
#define PRINTERSYSTEMWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ui/common/cardwidget/cardwidget.h"
#include <QKlipper/qklipper.h>

#include "ui/circularprogressbar.h"

class PrinterSystemWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterSystemWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterSystemWidget();

signals:

protected slots:
    void systemUpdateEvent();
    void setupUi();
    void convertBytes(qreal &bytes, QString &label);
    void sdInfoUpdateEvent();
    void onSystemCpuInfoChanged();
    void onSystemMemoryStatsChanged();

private:
    QKlipperSystem *m_system = nullptr;
    QKlipperSdInfo m_sdInfo;

    QHBoxLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_cpuClusterLayout = nullptr;

    QVBoxLayout *m_cpuLayout = nullptr;
    QVBoxLayout *m_sdLayout = nullptr;
    QVBoxLayout *m_temperatureLayout = nullptr;
    QVBoxLayout *m_memoryLayout = nullptr;

    QGroupBox *m_memoryGroupBox = nullptr;
    QGroupBox *m_cpuGroupBox = nullptr;
    QGroupBox *m_temperatureGroupBox = nullptr;

    CircularProgressBar *m_memoryProgress = nullptr;
    CircularProgressBar *m_cpuProgress = nullptr;
    CircularProgressBar *m_temperatureProgress = nullptr;

    QLabel *m_cpuNameLabel = nullptr;
    QLabel *m_cpuCountLabel = nullptr;
    QLabel *m_temperatureLabel = nullptr;
    QLabel *m_peakTemperatureLabel = nullptr;

    QLabel *m_memoryUsedLabel = nullptr;
    QLabel *m_memoryAvailableLabel = nullptr;
    QLabel *m_memoryCapacityLabel = nullptr;

    QGroupBox *m_sdGroupBox = nullptr;

    CircularProgressBar *m_sdProgress = nullptr;

    QLabel *m_sdUsedLabel = nullptr;
    QLabel *m_sdAvailableLabel = nullptr;
    QLabel *m_sdCapacityLabel = nullptr;

    qreal m_peakTemperature = 0.0;

    QWidget *m_centralWidget = nullptr;
};

#endif // PRINTERSYSTEMWIDGET_H
