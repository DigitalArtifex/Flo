#ifndef PRINTERUSEREDITOR_H
#define PRINTERUSEREDITOR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>

#include "ui/common/dialog/dialog.h"
#include "ui/QIconButton/qiconbutton.h"

#include <QKlipper/qklipper.h>

class PrinterUserEditor : public Dialog
{
    Q_OBJECT
public:
    explicit PrinterUserEditor(QWidget *parent = nullptr);
    ~PrinterUserEditor();

    QKlipperUser user();
    QString password();
    QString username();

signals:

protected slots:
    void setupUi();
    void acceptButtonClicked();
    void cancelButtonClicked();
    void validatePasswords(QString arg1);

private:
    QVBoxLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_buttonLayout = nullptr;

    QLabel *m_iconLabel = nullptr;

    QLineEdit *m_userNameEdit = nullptr;
    QLineEdit *m_userPasswordEdit = nullptr;
    QLineEdit *m_userPasswordVerifyEdit = nullptr;

    QIconButton *m_cancelButton = nullptr;
    QIconButton *m_acceptButton = nullptr;
};

#endif // PRINTERUSEREDITOR_H
