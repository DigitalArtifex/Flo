#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QMovie>

#include <QKlipper/qklipper.h>
#include <QtDAWidgets/qgaugewidget.h>

namespace Ui {
class SystemWidget;
}

class SystemWidget : public QFrame
{
    Q_OBJECT

public:
    explicit SystemWidget(QWidget *parent = nullptr);
    ~SystemWidget();

    void setUiClasses();
    void setPrinter(QKlipperInstance *printer);

    virtual void setStyleSheet(QString styleSheet);

private slots:
    void on_printer_klipperDisconnected(QKlipperInstance *printer);
    void on_printer_klipperConnected(QKlipperInstance *printer);

    void on_loadingAnimation_finished();

    void onSystemMemoryStatsChanged();
    void onSystemCpuInfoChanged();
    void onSystemHostnameChanged();

    //Private Functions
private:
    void convertBytes(qreal &bytes, QString &label);
    void convertDriveBytes(qreal &bytes, QString &label);
    void showLoadingScreen();
    void hideLoadingScreen();

private:
    Ui::SystemWidget *ui;

    QKlipperInstance *m_instance = nullptr;

    QGaugeWidget *m_systemCpuLoadProgressBar;
    QGaugeWidget *m_systemMemoryLoadProgressBar;
    QGaugeWidget *m_systemTemperatureProgressBar;

    QMovie *m_loadingGif = nullptr;
    QLabel *m_loadingLabel = nullptr;
};

#endif // SYSTEMWIDGET_H
