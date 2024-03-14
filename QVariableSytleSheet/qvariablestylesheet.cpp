#include "qvariablestylesheet.h"

QVariableStyleSheet::QVariableStyleSheet(QString stylesheet)
{
    _stylesheet = stylesheet;
}

void QVariableStyleSheet::setStyleSheet(QString stylesheet)
{
    _stylesheet = stylesheet;
}

QString QVariableStyleSheet::process()
{
    QString theme = _stylesheet;

    //Process CSS variables in QSS
    QRegularExpression rootExpression(":root\\s*\n*\\s*\\{\n*\\s*(--.*:.*;\n*)*\n*\\s*\\}", QRegularExpression::MultilineOption);
    QRegularExpression variableExpression("--[a-zA-Z0-9\\-\\_]+:\\s*[a-zA-Z0-9\\-\\_\\#]+;");
    QRegularExpression variableUsageExpression("var\\(--([a-zA-Z0-9\\-]*)*[\\)]{1}");
    QRegularExpression commentExpression("\\/\\*[^*]*\\*+([^/*][^*]*\\*+)*\\/");
    theme.remove(commentExpression);
    theme.replace(QRegularExpression("[\n]{2,}"), QString("\n"));
    theme.replace(QRegularExpression("[\\s]{2,}"), QString(" "));

    QRegularExpressionMatchIterator iterator = rootExpression.globalMatch(theme.toUtf8());
    QMap<QString, QString> variables;

    while(iterator.hasNext())
    {
        QRegularExpressionMatch rootMatch = iterator.next();
        QString root = rootMatch.captured(0);

        theme.remove(rootExpression);

        QRegularExpressionMatchIterator variableIterator = variableExpression.globalMatch(root.toUtf8());
        while(variableIterator.hasNext())
        {
            QRegularExpressionMatch variableMatch = variableIterator.next();
            QString variable = variableMatch.captured(0);

            QStringList split = variable.split(":");
            if(split.count() == 2)
            {
                QString key = split[0];
                QString value = split[1];

                while(value.startsWith(" "))
                    value.remove(0,1);

                while(key.startsWith(" "))
                    key.remove(0,1);
                value.remove(QRegularExpression(";$"));
                variables[key] = value;
            }
        }
    }

    iterator = variableUsageExpression.globalMatch(theme.toUtf8());

    while(iterator.hasNext())
    {
        QRegularExpressionMatch variableMatch = iterator.next();
        QString variable = variableMatch.captured(0);

        variable.remove("var(");
        variable.remove(QRegularExpression("\\)$"));

        QString replacement = variables[variable];
        theme.replace(variableMatch.captured(0), replacement);
    }

    //theme.remove(variableUsageExpression);

    return theme;
}
