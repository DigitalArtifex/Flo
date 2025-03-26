#ifndef PRINTEROVERVIEWWIDGET_H
#define PRINTEROVERVIEWWIDGET_H

#include <QFrame>
#include <QTimer>
#include <QQueue>
#include <QKlipper/QKlipperInstance/qklipperinstance.h>
#include <QKlipper/QKlipperPrinter/qklipperprinter.h>

namespace Ui {
class PrinterOverviewWidget;
}

class PrinterOverviewWidget : public QFrame
{
    Q_OBJECT

public:
    explicit PrinterOverviewWidget(QKlipperPrinter *printer, QWidget *parent = nullptr);
    ~PrinterOverviewWidget();

protected slots:
    void onPrinterStatusChanged();
    void onUpdateTimerTimeout();
    void onPrinterConnected(QKlipperInstance *instance);
    void onPrinterDisconnected(QKlipperInstance *instance);
    void calculateTotalWatts();
    void clearHeaterLabels();
    void setIcons();

protected:
    virtual void changeEvent(QEvent *event) override;

private slots:
    void on_restartFirmwareButton_clicked();

private:
    Ui::PrinterOverviewWidget *ui;
    QKlipperPrinter *m_printer = nullptr;

    //Use a timer instead of update signals to normalize timing of graph readings
    QTimer *m_updateTimer = nullptr;

    //To reduce log points, we will only save an entry once every 10 minutes
    QDateTime m_lastSave = QDateTime::fromSecsSinceEpoch(0);
    QQueue<qreal> m_saveBuffer;
};

#endif // PRINTEROVERVIEWWIDGET_H
