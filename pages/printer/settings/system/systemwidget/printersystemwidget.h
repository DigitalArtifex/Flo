/*
* PrinterSystemWidget
*
* Provides a widget for monitoring the printer system stats
*
* Copyright (C) 2024-2025 DigitalArtifex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PRINTERSYSTEMWIDGET_H
#define PRINTERSYSTEMWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "common/CardWidget/cardwidget.h"
#include <QKlipper/qklipper.h>

#include <QtDAWidgets/qgaugewidget.h>

#include "ui/QAccentLabel/qaccentlabel.h"

class PrinterSystemWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterSystemWidget(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterSystemWidget();


signals:

protected slots:
    void setIcons();
    void systemUpdateEvent();
    void setupUi();
    void convertBytes(qreal &bytes, QString &label);
    void sdInfoUpdateEvent();
    void onSystemCpuInfoChanged();
    void onSystemMemoryStatsChanged();
    void onPrinterMcuWakeTimeChanged();
    void onPrinterMcuFirmwareVersionChanged();
    void onPrinterMcuHardwareVersionChanged();
    void onPrinterMcuTaskAverageChanged();
    void onPrinterMcuFrequencyChanged();
    void onPrinterMcuChanged();

protected:
    virtual void changeEvent(QEvent *event);
    void convertDriveBytes(qreal &bytes, QString &label);

private:
    QKlipperSystem *m_system = nullptr;
    QKlipperPrinter *m_printer = nullptr;
    QKlipperSdInfo m_sdInfo;

    QGridLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_cpuClusterLayout = nullptr;

    QGridLayout *m_cpuLayout = nullptr;
    QGridLayout *m_sdLayout = nullptr;
    QVBoxLayout *m_temperatureLayout = nullptr;
    QGridLayout *m_memoryLayout = nullptr;

    QGroupBox *m_memoryGroupBox = nullptr;
    QGroupBox *m_cpuGroupBox = nullptr;
    QGroupBox *m_temperatureGroupBox = nullptr;

    QGaugeWidget *m_memoryProgress = nullptr;
    QGaugeWidget *m_cpuProgress = nullptr;
    QGaugeWidget *m_temperatureProgress = nullptr;

    QAccentLabel *m_cpuNameLabel = nullptr;
    QAccentLabel *m_cpuCountLabel = nullptr;
    QAccentLabel *m_temperatureLabel = nullptr;
    QAccentLabel *m_peakTemperatureLabel = nullptr;

    QAccentLabel *m_memoryUsedLabel = nullptr;
    QAccentLabel *m_memoryAvailableLabel = nullptr;
    QAccentLabel *m_memoryCapacityLabel = nullptr;

    QGroupBox *m_sdGroupBox = nullptr;

    QGaugeWidget *m_sdProgress = nullptr;

    QAccentLabel *m_sdUsedLabel = nullptr;
    QAccentLabel *m_sdAvailableLabel = nullptr;
    QAccentLabel *m_sdCapacityLabel = nullptr;

    qreal m_peakTemperature = 0.0;

    QWidget *m_centralWidget = nullptr;



    QKlipperMCU *m_mcu;

    QHBoxLayout *m_mcuProgressLayout = nullptr;
    QVBoxLayout *m_mcuLayout = nullptr;

    QGroupBox *m_mcuGroupBox = nullptr;

    QGaugeWidget *m_mcuAverageProgressBar = nullptr;

    QAccentLabel *m_frequencyLabel = nullptr;
    QAccentLabel *m_hardwareLabel = nullptr;
    QAccentLabel *m_firmwareLabel = nullptr;
    QAccentLabel *m_wakeTimeLabel = nullptr;

    QWidget *m_mcuProgressWidget = nullptr;
};

#endif // PRINTERSYSTEMWIDGET_H
