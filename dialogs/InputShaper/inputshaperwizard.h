#ifndef INPUTSHAPERWIZARD_H
#define INPUTSHAPERWIZARD_H

#include <QWizard>
#include <QKlipper/qklipper.h>
#include <QtDAWidgets/DAWidgets>
#include <QListWidgetItem>

#include "ui/messagedialog.h"

namespace Ui
{
    class InputShaperWizard;
}

class InputShaperWizard : public QWizard
{
        Q_OBJECT

    public:
        explicit InputShaperWizard(QKlipperInstance *instance, QWidget *parent = nullptr);
        ~InputShaperWizard();

        virtual bool validateCurrentPage() override;

    private slots:
        void savePrinterSettings();
        bool saveConfig();
        bool configurePrinter();
        void disableSquareCornerVelocity(QKlipperError *error);
        void disableMinimumCruiseRatio(QKlipperError *error);
        void disablePressureAdvance(QKlipperError *error);
        void disableInputShaper(QKlipperError *error);

        bool resetPrinterSettings();
        void resetSquareCornerVelocity(QKlipperError *error);
        void resetMinimumCruiseRatio(QKlipperError *error);
        void resetPressureAdvance(QKlipperError *error);
        void setInputShaper(QKlipperError *error);
        void onServerFileListChanged();
        void showErrorMessage(QString message);
        bool printCurrentFile();

        qreal getXResonance();
        qreal getYResonance();

        bool setupTuningTower();

        void on_InputShaperWizard_currentIdChanged(int id);

        void on_InputShaperWizard_rejected();

        void on_reRunButton_clicked();

        void on_saveButton_clicked();

        void on_fileListWidget_itemDoubleClicked(QListWidgetItem *item);

        void on_fileListWidget_itemSelectionChanged();

    private:
        Ui::InputShaperWizard *ui;

        QString m_currentDirectory = "gcodes";

        QKlipperInstance *m_instance = nullptr;
        qreal m_squareCornerVelocity = 5.0;
        qreal m_minimumCruiseRatio = 0.0;
        qreal m_pressureAdvance = 0.0;

        QString m_selectedFile;

        bool m_printerConfigured = false;
        bool m_fileSelected = false;
        bool m_printingStarted = false;
        bool m_secondPrintingStarted = false;

        int m_forcedId = -1;
};

#endif // INPUTSHAPERWIZARD_H
