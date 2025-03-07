#ifndef NEWFOLDERDIALOG_H
#define NEWFOLDERDIALOG_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>

#include "common/dialog/dialog.h"
#include "ui/QIconButton/qiconbutton.h"

class NewFolderDialog : public Dialog
{
    Q_OBJECT
public:
    explicit NewFolderDialog(QWidget *parent = nullptr);
    ~NewFolderDialog();

    QString value() const;

protected:
    void setupUi();

private:
    QGridLayout *m_layout = nullptr;
    QLineEdit *m_lineEdit = nullptr;
    QLabel *m_textLabel = nullptr;

    QIconButton *m_acceptButton = nullptr;
    QIconButton *m_cancelButton = nullptr;

};

#endif // NEWFOLDERDIALOG_H
