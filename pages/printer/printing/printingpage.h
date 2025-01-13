#ifndef PRINTINGPAGE_H
#define PRINTINGPAGE_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QGridLayout>
#include <QSlider>

#include <ui/qgaugewidget.h>
#include <ui/qanimatedwidget.h>
#include <ui/common/cardwidget/cardwidget.h>
#include <pages/printer/widgets/printerwebcam/printerwebcamwidget.h>
#include <pages/printer/job/printjobwidget.h>

class PrintingPage : public QFrame
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit PrintingPage(QKlipperPrinter *printer, QWidget *parent = nullptr);

    signals:

    protected slots:

        void onPrinterETAChanged();
        void onPrinterFileChanged();
        void onPrinterFileMetaDataChanged();
        void onPrinterGCodeMoveChanged();
        void onPrintJobChanged();
        void onPrintJobCurrentLayerChanged();
        void onPrintJobTotalLayerChanged();
        void onPrintJobFilamentUsedChanged();
        void onExtruderTargetTemperatureChanged();
        void onExtruderExtrusionSpeedChanged();
        void onBedTargetTemperatureChanged();
        void onToolheadCurrentExtruderChanged();

    protected:
        void initValues();
        void setupUI();
        void setupIcons();

        virtual void changeEvent(QEvent *event) override;
        virtual void resizeEvent(QResizeEvent *event) override;

    private:
        QKlipperFile *m_currentFile = nullptr;
        QKlipperExtruder *m_currentExtruder = nullptr;
        QKlipperPrintJob *m_printJob = nullptr;
        QKlipperPrinter *m_printer = nullptr;
        QGridLayout *m_mainLayout = nullptr;

        QWidget *m_infoWidget = nullptr;
        QWidget *m_infoPanelWidget = nullptr;
        QHBoxLayout *m_infoLayout = nullptr;
        QVBoxLayout *m_infoLabelsLayout = nullptr;
        QLabel *m_printPreviewLabel = nullptr;
        QLabel *m_filenameLabel = nullptr;
        QLabel *m_etaLabel = nullptr;
        QLabel *m_messageLabel = nullptr;
        QLabel *m_currentLayerLabel = nullptr;
        QLabel *m_totalLayerLabel = nullptr;
        QLabel *m_extruderTargetTempLabel = nullptr;
        QLabel *m_bedTargetTempLabel = nullptr;
        QPixmap m_printPreviewPixmap;

        QWidget *m_buttonBoxWidget = nullptr;
        QVBoxLayout *m_buttonBoxLayout = nullptr;
        QIconButton *m_cancelPrintButton = nullptr;
        QIconButton *m_pausePrintButton = nullptr;

        QFrame *m_sliderBoxFrame = nullptr;
        QVBoxLayout *m_sliderBoxLayout = nullptr;
        QLabel *m_printSpeedText = nullptr;
        QSlider *m_printSpeedSlider = nullptr;
        QLabel *m_extrusionSpeedText = nullptr;
        QSlider *m_extrusionSpeedSlider = nullptr;

        QFrame *m_statusWidget = nullptr;
        QGridLayout *m_statusLayout = nullptr;
        QGaugeWidget *m_printProgressBar = nullptr;

        QLabel *m_timeRemainingLabel = nullptr;
        QLabel *m_timeRemainingTextLabel = nullptr;

        QWidget *m_materialStatusWidget = nullptr;
        QVBoxLayout *m_materialStatusLayout = nullptr;
        QLabel *m_materialUsedLabel = nullptr;
        QLabel *m_materialRemainingLabel = nullptr;

        PrintJobWidget *m_printJobWidget = nullptr;

        PrinterWebcamWidget *m_printerWebcam = nullptr;
        CardWidget *m_printerWebcamCard = nullptr;
};

#endif // PRINTINGPAGE_H
