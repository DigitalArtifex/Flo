#ifndef PRINTERSERVICEWIDGET_H
#define PRINTERSERVICEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QLabel>
#include <QSpacerItem>

#include "ui/common/cardwidget/cardwidget.h"
#include "ui/QIconButton/qiconbutton.h"

#include "types/system.h"

class PrinterServiceWidget : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterServiceWidget(System *system, System::ServiceState service, QWidget *parent = nullptr);

signals:

protected slots:
    void setupUi();
    void serviceStatesUpdateEvent();

    void stopButtonClickEvent(bool checked = false);
    void startButtonClickEvent(bool checked = false);
    void restartButtonClickEvent(bool checked = false);

private:
    System *m_system = nullptr;
    System::ServiceState m_service;

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
