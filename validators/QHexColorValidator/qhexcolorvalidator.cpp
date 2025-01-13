#include "qhexcolorvalidator.h"

QHexColorValidator::QHexColorValidator(QObject *parent)
    : QValidator{parent}
{

}

QHexColorValidator::~QHexColorValidator()
{

}

QValidator::State QHexColorValidator::validate(QString &text, int &pos) const
{
    if(text.contains(m_hexExpression))
    {
        if(pos)
            pos = text.indexOf(m_hexExpression);

        return QValidator::Acceptable;
    }

    return QValidator::Intermediate;
}
