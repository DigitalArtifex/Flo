#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>

#include "job/printjoblistwidget.h"
#include "energy/energyconsumptionwidget.h"
#include "issue/issuelistwidget.h"

namespace Ui {
class StatusWidget;
}

class StatusWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit StatusWidget(QWidget *parent = nullptr);
    ~StatusWidget();

    void setUiClasses();
    void loadPrintJobs();

    virtual void setStyleSheet(QString styleSheet);

private slots:
    void on_printerPool_jobStarted(PrintJob *job);
    void on_printerPool_jobFinished(PrintJob *job);
    void on_printerPool_jobUpdated(PrintJob *job);

private:
    void setupJobPage();
    void setupEnergyPage();
    void setupIssuesPage();

private:
    Ui::StatusWidget *ui;
    PrintJobListWidget *_printJobList = nullptr;
    EnergyConsumptionWidget *_energyConsumption = nullptr;
    IssueListWidget *_issueList = nullptr;
};

#endif // STATUSWIDGET_H
