#ifndef PRINTJOBWIDGET_H
#define PRINTJOBWIDGET_H

#include <QTabWidget>
#include <QGridLayout>

#include "printjoblistwidget.h"

namespace Ui {
class PrintJobWidget;
}

class PrintJobWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit PrintJobWidget(QWidget *parent = nullptr);
    ~PrintJobWidget();

    void setUiClasses();
    void loadPrintJobs();

    virtual void setStyleSheet(QString styleSheet);

private slots:
    void on_printerPool_jobStarted(PrintJob *job);
    void on_printerPool_jobFinished(PrintJob *job);
    void on_printerPool_jobUpdated(PrintJob *job);

private:
    Ui::PrintJobWidget *ui;
    PrintJobListWidget *_printJobList = nullptr;
};

#endif // PRINTJOBWIDGET_H
