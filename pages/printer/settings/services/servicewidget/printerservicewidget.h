#ifndef PRINTERSERVICEWIDGET_H
#define PRINTERSERVICEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QLabel>
#include <QSpacerItem>

#include "common/CardWidget/cardwidget.h"
#include "ui/QIconButton/qiconbutton.h"

#include <QKlipper/qklipper.h>

class PrinterServiceWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterServiceWidget(QKlipperSystem *system, QKlipperService *service, QWidget *parent = nullptr);
    void setServiceState(QKlipperService *service);

signals:

protected slots:
    void setupUi();

    void onServiceStateChanged();
    void onServiceSubStateChanged();

    void stopButtonClickEvent(bool checked = false);
    void startButtonClickEvent(bool checked = false);
    void restartButtonClickEvent(bool checked = false);

    virtual void setStyleSheet(const QString &styleSheet);

private:
    QKlipperSystem *m_system = nullptr;
    QKlipperService *m_service;

    QLabel *m_stateLabel = nullptr;
    QLabel *m_subStateLabel = nullptr;
    QSpacerItem *m_spacerItem = nullptr;

    QWidget *m_centralWidget = nullptr;

    QVBoxLayout *m_centralLayout = nullptr;

    QToolButton *m_stopButton = nullptr;
    QToolButton *m_startButton = nullptr;
    QToolButton *m_restartButton = nullptr;
};

#endif // PRINTERSERVICEWIDGET_H
