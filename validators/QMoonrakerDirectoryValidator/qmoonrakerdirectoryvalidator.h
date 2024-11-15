#ifndef QMOONRAKERDIRECTORYVALIDATOR_H
#define QMOONRAKERDIRECTORYVALIDATOR_H

#include <QObject>
#include <QValidator>
#include <QDir>

class QMoonrakerDirectoryValidator : public QValidator
{
        Q_OBJECT
    public:
        explicit QMoonrakerDirectoryValidator(QObject *parent = nullptr);

        virtual QValidator::State validate(QString &text, int &pos) const;

    private:
        QRegularExpression m_httpExpression = QRegularExpression("^\\s*(http|https)\\:\\/\\/");
};

#endif // QMOONRAKERDIRECTORYVALIDATOR_H
