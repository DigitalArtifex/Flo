#ifndef PRINTERBEDTOOLSDIALOG_H
#define PRINTERBEDTOOLSDIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QGridLayout>
#include <QScreen>

#include <ui/common/dialog/dialog.h>
#include <ui/ProgressDialog/progressdialog.h>
#include <ui/QIconButton/qiconbutton.h>

#include <QKlipper/qklipper.h>

#include <pages/printer/bedmesh/bedmeshwidget.h>

class PrinterBedToolsDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit PrinterBedToolsDialog(QKlipperPrintBed *bed, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onPidTuneButtonClicked();
        void onCalibrateMeshButtonClicked();
        void onCalibrateScrewsButtonClicked();
        void onMeshViewerButtonClicked();

        void setupUi();

    private:
        QKlipperPrintBed *m_printerBed = nullptr;

        QGridLayout *m_centralLayout = nullptr;

        QIconButton *m_pidTuneButton = nullptr;
        QIconButton *m_calibrateMeshButton = nullptr;
        QIconButton *m_calibrateScrewsButton = nullptr;
        QIconButton *m_meshViewerButton = nullptr;
};

#endif // PRINTERBEDTOOLSDIALOG_H
