#ifndef QMOONRAKERVALIDATOR_H
#define QMOONRAKERVALIDATOR_H

#include <QObject>
#include <QDir>
#include <QValidator>
#include <QRegularExpression>

class QMoonrakerValidator : public QValidator
{
    Q_OBJECT
public:
    explicit QMoonrakerValidator(QObject *parent = nullptr);
    ~QMoonrakerValidator();

    virtual QValidator::State validate(QString &text, int &pos) const;

private:
    QRegularExpression m_httpExpression = QRegularExpression("^\\s*(http|https)\\:\\/\\/");
};

#endif // QMOONRAKERVALIDATOR_H
