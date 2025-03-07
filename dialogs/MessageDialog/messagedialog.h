#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "common/dialog/dialog.h"
#include "ui/QIconButton/qiconbutton.h"

class MessageDialog : public Dialog
{
    Q_OBJECT
public:
    explicit MessageDialog(QWidget *parent = nullptr);
    ~MessageDialog();

    QIcon icon() const;

    QString text() const;

    QString informativeText() const;

public slots:
    void setIcon(const QIcon &icon);
    void setText(const QString &text);
    void setRejectEnabled(bool enabled);

    void setInformativeText(const QString &informativeText);

signals:

protected slots:
    void setupUi();

private:
    QVBoxLayout *m_centralLayout = nullptr;
    QHBoxLayout *m_informationLayout = nullptr;
    QHBoxLayout *m_buttonLayout = nullptr;

    QIcon m_icon;
    QString m_text;
    QString m_informativeText;

    QLabel *m_textLabel = nullptr;
    QLabel *m_informativeTextLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QIconButton *m_acceptButton = nullptr;
    QIconButton *m_rejectButton = nullptr;
};

#endif // MESSAGEDIALOG_H
