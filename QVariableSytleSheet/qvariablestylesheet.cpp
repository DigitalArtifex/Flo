#include "qvariablestylesheet.h"

QVariableStyleSheet::QVariableStyleSheet(QString stylesheet)
{
    m_stylesheet = stylesheet;
}

void QVariableStyleSheet::setStyleSheet(QString stylesheet)
{
    m_stylesheet = stylesheet;
}

QString QVariableStyleSheet::process()
{
    QString theme = m_stylesheet;

    //Process CSS variables in QSS
    theme.remove(commentExpression);

    theme.replace(QRegularExpression("[\n]+"), QString("\n"));

    QRegularExpressionMatchIterator iterator = rootExpression.globalMatch(theme.toUtf8());
    QMap<QString, QString> variables;

    if(iterator.hasNext())
    {
        QRegularExpressionMatch rootMatch = iterator.next();
        QString root = rootMatch.captured(0);

        theme.remove(rootExpression);
        m_rawStyleSheet = theme;

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

                if(key.startsWith("--"))
                    key = key.mid(2);

                qDebug() << key << value;

                m_variables[key] = value;
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
    }

    return theme;
}

QMap<QString, QString> QVariableStyleSheet::variables() const
{
    return m_variables;
}

void QVariableStyleSheet::setVariables(const QMap<QString, QString> &variables)
{
    m_variables = variables;
}

QString QVariableStyleSheet::rawStyleSheet() const
{
    return m_rawStyleSheet;
}

void QVariableStyleSheet::setRawStyleSheet(const QString &newRawStyleSheet)
{
    m_rawStyleSheet = newRawStyleSheet;
}
