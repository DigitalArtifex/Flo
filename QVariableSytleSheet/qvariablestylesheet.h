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

private:
    QString m_stylesheet;
    QMap<QString, QString> m_variables;
    QRegularExpression rootExpression = QRegularExpression(":root\\s*\n*\\s*\\{\n*\\s*(--.*:.*;\n*)*\n*\\s*\\}", QRegularExpression::MultilineOption);
    QRegularExpression variableExpression = QRegularExpression("--[a-zA-Z0-9\\-\\_]+:\\s*[a-zA-Z0-9\\-\\_\\#]+;");
    QRegularExpression variableUsageExpression = QRegularExpression("var\\(--([a-zA-Z0-9\\-]*)*[\\)]{1}");
    QRegularExpression commentExpression = QRegularExpression("\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/");
};

#endif // QVARIABLESTYLESHEET_H
