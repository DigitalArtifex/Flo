#ifndef QGCODEMACRO_H
#define QGCODEMACRO_H

#include <QObject>
#include <QList>
#include <QMap>

class QGCodeMacro {
    Q_GADGET
public:
    QString macro;
    QString description;
    QString gcode;
    QString replaces;
    QMap<QString,QString> variables;
};

typedef QList<QGCodeMacro> QGCodeMacroList;

#endif // QGCODEMACRO_H
