#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "common/dialog/dialog.h"
#include "QIconButton/qiconbutton.h"

class MessageDialog : public Dialog
{
    Q_OBJECT
public:
    explicit MessageDialog(QWidget *parent = nullptr);

    QIcon icon() const;

    QString text() const;

public slots:
    void setIcon(const QIcon &icon);
    void setText(const QString &text);

signals:

protected slots:
    void setupUi();
    void acceptButtonClicked();

private:
    QVBoxLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_informationLayout = nullptr;

    QIcon m_icon;
    QString m_text;

    QLabel *m_textLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QIconButton *m_acceptButton = nullptr;
};

#endif // MESSAGEDIALOG_H
