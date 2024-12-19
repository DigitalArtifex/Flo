#ifndef PRINTERBEDINFODIALOG_H
#define PRINTERBEDINFODIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QMap>
#include <QGridLayout>
#include <QTableWidget>
#include <QResizeEvent>

#include <ui/common/dialog/dialog.h>

#include <QKlipper/qklipper.h>

class PrinterBedInfoDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        PrinterBedInfoDialog(QKlipperPrintBed *bed, QWidget *parent = nullptr);
        ~PrinterBedInfoDialog();

    protected slots:
        void setupUi();
        void onCurrentTempChanged();
        void onHasBedMeshResultChanged();
        void onHasAdjustmentScrewResultChanged();
        void onHeaterPinChanged();
        void onInlineResistorChanged();
        void onMaxPowerChanged();
        void onMaxTempChanged();
        void onMinTempChanged();
        void onPidKDChanged();
        void onPidKIChanged();
        void onPidKPChanged();
        void onPowerChanged();
        void onPullupResistorChanged();
        void onPwmCycleTimeChanged();
        void onSensorPinChanged();
        void onSensorTypeChanged();
        void onSmoothTimeChanged();
        void onTargetTempChanged();
        void onTiltAdjustErrorChanged();

    protected:
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;
        QTableWidget *m_infoTable;
        QMap<QString, QTableWidgetItem*> m_itemMap;

        QKlipperPrintBed *m_printBed = nullptr;
};

#endif // PRINTERBEDINFODIALOG_H
