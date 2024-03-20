#ifndef PRINTERDEFINITION_H
#define PRINTERDEFINITION_H

#include <QObject>
#include <QString>

class PrinterDefinition
{
    Q_GADGET
public:
    QString name;
    QString id;
    QString instanceLocation;
    QString klipperLocation;
    QString moonrakerLocation;
    QString configLocation;
    QString gcodeLocation;
    QString configFile;
    QString apiKey;
    bool autoConnect = true;
    bool defaultPrinter = false;
};

typedef QList<PrinterDefinition> PrinterDefinitionList;
#endif // PRINTERDEFINITION_H
