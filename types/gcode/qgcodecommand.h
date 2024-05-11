#ifndef QGCODECOMMAND_H
#define QGCODECOMMAND_H

#include <QObject>
#include <QString>

class QGCodeCommand
{
    Q_GADGET
public:
    QString command;
    QString help;
};

typedef QList<QGCodeCommand> QGCodeCommandList;
#endif // QGCODECOMMAND_H
