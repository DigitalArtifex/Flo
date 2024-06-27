#ifndef QHEXCOLORVALIDATOR_H
#define QHEXCOLORVALIDATOR_H

#include <QObject>
#include <QValidator>

class QHexColorValidator : public QValidator
{
    Q_OBJECT
public:
    explicit QHexColorValidator(QObject *parent = nullptr);
    ~QHexColorValidator();

    virtual QValidator::State validate(QString &text, int &pos) const;

private:
    QRegularExpression m_hexExpression = QRegularExpression("^\\s*\\#[a-f|A-F|0-9]{6}");
};

#endif // QHEXCOLORVALIDATOR_H
