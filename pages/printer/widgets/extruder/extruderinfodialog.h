#ifndef EXTRUDERINFODIALOG_H
#define EXTRUDERINFODIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QTableWidget>
#include <QResizeEvent>

#include <ui/common/dialog/dialog.h>
#include <QKlipper/qklipper.h>

class ExtruderInfoDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit ExtruderInfoDialog(QKlipperExtruder *extruder, QWidget *parent = nullptr);
        ~ExtruderInfoDialog();

    signals:

    protected slots:
        void onGearRatioChanged();
        void onFullStepsPerRoatationChanged();
        void onCurrentTempChanged();
        void onTargetTempChanged();
        void onSmoothTimeChanged();
        void onPressureAdvanceChanged();
        void onExtrusionFactorChanged();
        void onFilamentDiameterChanged();
        void onNozzleDiameterChanged();
        void onPowerChanged();
        void onInlineResistorChanged();
        void onPullupResistorChanged();
        void onPwmCycleChanged();
        void onRotationDistanceChanged();
        void onInstantCornerVelocityChanged();
        void onPidKDChanged();
        void onPidKIChanged();
        void onPidKPChanged();
        void onMaxExtrudeCrossSectionChanged();
        void onMaxExtrudeOnlyAccelerationChanged();
        void onMaxExtrudeOnlyDistanceChanged();
        void onMaxExtrudeOnlyVelocityChanged();
        void onMaxTempChanged();
        void onMaxPowerChanged();
        void onMicrostepsChanged();
        void onMinExtrudeTempChanged();
        void onMinTempChanged();
        void onCanExtrudeChanged();
        void onNameChanged();
        void onControlPinChanged();
        void onDirPinChanged();
        void onEnablePinChanged();
        void onHeaterPinChanged();
        void onSensorPinChanged();
        void onSensorTypeChanged();
        void onStepPinChanged();
        void onOffsetChanged();
        void onPressureAdvanceSmoothTimeChanged();
        void addTableItem(const QString &name);
        void reset();
        void setupUi();

    protected:
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QKlipperExtruder *m_extruder = nullptr;

        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;
        QTableWidget *m_infoTable;
        QMap<QString, QTableWidgetItem*> m_itemMap;
};

#endif // EXTRUDERINFODIALOG_H
