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
    static void loadPrinters(QObject *parent);

    static Printer *getPrinterById(QString id);
    static QStringList keys();
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
    void printerError(QString title, QString message, Printer *printer);
    void printJobStarted(PrintJob *printJob);
    void printJobFinished(PrintJob *printJob);

private slots:
    void on_printerAdded(Printer *printer);
    void on_printerRemoved(Printer *printer);
    void on_printerUpdated(Printer *printer);
    void on_printerError(QString title, QString message, Printer *printer);

    void on_printJob_started(PrintJob *printJob);
    void on_printJob_finished(PrintJob *printJob);

private:
    explicit PrinterPool();
    static PrinterPool *m_instance;
    static QMap<QString,Printer*> m_printerPool;
};

#endif // PRINTERPOOL_H
