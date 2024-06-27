#ifndef QHTTPVALIDATOR_H
#define QHTTPVALIDATOR_H

#include <QObject>
#include <QValidator>

class QHttpValidator : public QValidator
{
    Q_OBJECT
public:
    explicit QHttpValidator(QObject *parent = nullptr);
    ~QHttpValidator();

    virtual QValidator::State validate(QString &text, int &pos) const;

private:
    QRegularExpression m_httpExpression = QRegularExpression("^\\s*(http|https)\\:\\/\\/");
};

#endif // QHTTPVALIDATOR_H
