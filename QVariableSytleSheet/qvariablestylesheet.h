#ifndef QVARIABLESTYLESHEET_H
#define QVARIABLESTYLESHEET_H

#include <QObject>
#include <QMap>
#include <QRegularExpression>

class QVariableStyleSheet
{
    Q_GADGET
public:
    QVariableStyleSheet(QString stylesheet = QString(""));

    void setStyleSheet(QString stylesheet);
    QString process();

private:
    QString _stylesheet;
};

#endif // QVARIABLESTYLESHEET_H
