#include "qhttpvalidator.h"

QHttpValidator::QHttpValidator(QObject *parent)
    : QValidator{parent}
{

}

QHttpValidator::~QHttpValidator()
{

}

QValidator::State QHttpValidator::validate(QString &text, int &pos) const
{
    if(text.contains(m_httpExpression))
    {
        if(pos)
            pos = text.indexOf(m_httpExpression);

        return QValidator::Acceptable;
    }

    return QValidator::Intermediate;
}
