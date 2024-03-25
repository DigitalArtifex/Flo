#ifndef PRINTERPOOL_H
#define PRINTERPOOL_H

#include <QObject>
#include <QMap>
#include "../types/printerdefinition.h"
#include "../types/printjob.h"

class Printer;

class PrinterPool : public QObject
{
    Q_OBJECT
public:
    static void loadPrinters();

    static Printer *getPrinterById(QString id);
    static void addPrinter(PrinterDefinition definition);
    static void removePrinter(PrinterDefinition definition);
    static void updatePrinter(PrinterDefinition definition);

    static bool contains(QString id);

    static long printersOnline();
    static long printersAvailable();
    static long printersRunning();

    static QList<PrintJob*> printJobs();
    static PrinterPool *instance();

signals:
    void printerAdded(Printer *printer);
    void printerRemoved(Printer *printer);
    void printerUpdated(Printer *printer);
    void jobStarted(PrintJob *job);
    void jobFinished(PrintJob *job);
    void jobUpdated(PrintJob *job);

private:
    void on_printerAdded(Printer *printer);
    void on_printerRemoved(Printer *printer);
    void on_printerUpdated(Printer *printer);
    void on_jobStarted(PrintJob *job);
    void on_jobFinished(PrintJob *job);
    void on_jobUpdated(PrintJob *job);

private:
    explicit PrinterPool();
    static PrinterPool *_instance;
    static QMap<QString,Printer*> _printerPool;
};

#endif // PRINTERPOOL_H
