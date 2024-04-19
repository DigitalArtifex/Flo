#ifndef PRINTERPAGE_H
#define PRINTERPAGE_H

#include <QFrame>
#include <QMap>

#include "extruderwidget.h"
#include "../../types/printer.h"

#include "filebrowser/filebrowser.h"
#include "bedmesh/bedmeshwidget.h"
#include "offline/printerofflinescreen.h"
#include "terminal/printerterminal.h"

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

private slots:
    void on_xPosDecreaseButton_clicked();
    void on_terminalButton_toggled(bool checked);
    void on_overviewButton_toggled(bool checked);
    void on_filesButton_toggled(bool checked);
    void on_bedMeshButton_toggled(bool checked);
    void on_settingsButton_toggled(bool checked);
    void on_printerUpdate(Printer *printer);

private:
    CircularProgressBar *_bedTemperatureBar;
    CircularProgressBar *_chamberTemperatureBar;
    CircularProgressBar *_extruderTemperatureBar;

    FileBrowser *_fileBrowser = nullptr;
    FileBrowser *_configBrowser = nullptr;
    BedMeshWidget *_bedMeshWidget = nullptr;
    PrinterOfflineScreen *_printerOfflineScreen = nullptr;
    PrinterTerminal *_terminal = nullptr;

    QMap<int, ExtruderWidget*> _extruderMap;

    Printer *_printer = nullptr;

    Ui::PrinterPage *ui;
    void setupUiClasses();
};

#endif // PRINTERPAGE_H
