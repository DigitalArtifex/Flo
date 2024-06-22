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
    Q_PROPERTY(bool isAnimating READ animating WRITE setAnimating NOTIFY animatingChanged FINAL)
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

    bool animating() const;
    void setAnimating(bool animating);

signals:
    void animatingChanged(bool);

protected:
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);

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

    void on_positionResetButton_clicked();

    void on_positionApplyButton_clicked();

private:

    CircularProgressBar *m_chamberTemperatureBar;
    CircularProgressBar *m_extruderTemperatureBar;

    FileBrowser *m_fileBrowser = nullptr;
    FileBrowser *m_overviewBrowser = nullptr;
    FileBrowser *m_configBrowser = nullptr;

    Q3DPrintBedMeshWidget *m_bedMeshWidget = nullptr;
    PrinterOfflineScreen *m_printerOfflineScreen = nullptr;
    PrinterTerminal *m_terminal = nullptr;

    bool xPosEditing = false;
    bool yPosEditing = false;
    bool zPosEditing = false;

    QMap<int, ExtruderWidget*> m_extruderMap;

    Printer *m_printer = nullptr;

    PrinterBedWidget *m_printerBedWidget = nullptr;

    Ui::PrinterPage *ui;
    void setupUiClasses();

    void addFanLabels(Fan *fan, QString name);

    QFlowLayout *m_centerLayout = nullptr;
    QSpacerItem *m_centerLayoutBottomSpacer = nullptr;

    PrinterWebcamWidget *m_webcamWidget = nullptr;

    ToolHeadControlFrame *m_toolheadControlFrame = nullptr;

    bool m_animating = false;


    QRegularExpression m_number_expression = QRegularExpression("\\d+");
};

#endif // PRINTERPAGE_H
