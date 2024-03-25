#ifndef PRINTJOB_H
#define PRINTJOB_H

#include <QObject>

class PrintJob
{
    Q_GADGET
public:
    QString printerName;
    QString printerId;
    QString fileName;
    QString fileId;
    QString startDate;
    QString endDate;
    qreal progress;
};

#endif // PRINTJOB_H
