#ifndef PRINTERPAGE_H
#define PRINTERPAGE_H

#include <QFrame>
#include <QMap>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include <QShowEvent>

#include "widgets/extruder/extruderwidget.h"
#include "../../types/printer.h"

#include "filebrowser/filebrowser.h"
#include "bedmesh/bedmeshwidget.h"
#include "offline/printerofflinescreen.h"
#include "terminal/printerterminal.h"

#include "widgets/printerbed/printerbedwidget.h"
#include "widgets/printerwebcam/printerwebcamwidget.h"
#include "../../ui/layouts/qflowlayout.h"

#include "widgets/toolhead/control/toolheadcontrolframe.h"

namespace Ui {
class PrinterPage;
}

class PrinterPage : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterPage(Printer *printer, QWidget *parent = nullptr);
    ~PrinterPage();
    void addExtruder(Extruder *extruder, QString name = QString("Extruder"));

    virtual void setStyleSheet(QString styleSheet);
    void setIcons();

    Printer *printer() const;
    void setPrinter(Printer *printer);

    virtual void resizeEvent(QResizeEvent *event);
    virtual void setPrintActionsEnabled(bool enabled);

protected:
    virtual void showEvent(QShowEvent *event);

private slots:
    void on_xPosDecreaseButton_clicked();
    void on_terminalButton_toggled(bool checked);
    void on_overviewButton_toggled(bool checked);
    void on_filesButton_toggled(bool checked);
    void on_bedMeshButton_toggled(bool checked);
    void on_settingsButton_toggled(bool checked);
    void on_printerUpdate(Printer *printer);

    void on_homeToolheadButton_clicked();

    void on_restartFirmwareButton_clicked();

    void on_posIncrementSelect_currentTextChanged(const QString &arg1);

    void on_xPosIncreaseButton_clicked();
    void on_yPosDecreaseButton_clicked();
    void on_yPosIncreaseButton_clicked();
    void on_zPosDecreaseButton_clicked();
    void on_zPosIncreaseButton_clicked();

    void on_xHomeButton_clicked();
    void on_yHomeButton_clicked();
    void on_zHomeButton_clicked();

    void on_xDestinationSpinBox_valueChanged(double arg1);

    void on_yDestinationSpinBox_valueChanged(double arg1);

    void on_zDestinationSpinBox_valueChanged(double arg1);

private:

    CircularProgressBar *_chamberTemperatureBar;
    CircularProgressBar *_extruderTemperatureBar;

    FileBrowser *_fileBrowser = nullptr;
    FileBrowser *_overviewBrowser = nullptr;
    FileBrowser *_configBrowser = nullptr;

    Q3DPrintBedMeshWidget *_bedMeshWidget = nullptr;
    PrinterOfflineScreen *_printerOfflineScreen = nullptr;
    PrinterTerminal *_terminal = nullptr;

    bool xPosEditing = false;
    bool yPosEditing = false;
    bool zPosEditing = false;

    QMap<int, ExtruderWidget*> _extruderMap;

    Printer *_printer = nullptr;

    PrinterBedWidget *_printerBedWidget = nullptr;

    Ui::PrinterPage *ui;
    void setupUiClasses();

    void addFanLabels(Fan *fan, QString name);

    QFlowLayout *_centerLayout = nullptr;
    QSpacerItem *_centerLayoutBottomSpacer = nullptr;

    PrinterWebcamWidget *_webcamWidget = nullptr;

    ToolHeadControlFrame *_toolheadControlFrame = nullptr;
};

#endif // PRINTERPAGE_H
