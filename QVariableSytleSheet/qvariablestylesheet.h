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

    QMap<QString, QString> variables() const;
    void setVariables(const QMap<QString, QString> &variables);

    QString rawStyleSheet() const;

    void setRawStyleSheet(const QString &newRawStyleSheet);

private:
    QString m_stylesheet;
    QString m_rawStyleSheet;

    QMap<QString, QString> m_variables;
    QRegularExpression rootExpression = QRegularExpression("^:root\\s*{\\s*(--[a-zA-Z0-9\\-\\_]+:\\s*[a-zA-Z0-9\\-\\_\\#]+;\\s*)*}\\s*", QRegularExpression::MultilineOption);
    QRegularExpression variableExpression = QRegularExpression("--[a-zA-Z0-9\\-\\_]+:\\s*[a-zA-Z0-9\\-\\_\\#]+;");
    QRegularExpression variableUsageExpression = QRegularExpression("var\\(--([a-zA-Z0-9\\-]*)*[\\)]{1}");
    QRegularExpression commentExpression = QRegularExpression("\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/\\s*");
    QRegularExpression emptyLineExpression = QRegularExpression("^[\\s]+\\n");
};

#endif // QVARIABLESTYLESHEET_H
