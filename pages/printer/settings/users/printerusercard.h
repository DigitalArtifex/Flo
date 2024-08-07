#ifndef PRINTERUSERCARD_H
#define PRINTERUSERCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "ui/common/cardwidget/cardwidget.h"

#include "types/system.h"

class PrinterUserCard : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterUserCard(System::User user, QWidget *parent = nullptr);
    ~PrinterUserCard();

    System::User user() const;

public slots:
    void setUser(const System::User &user);

signals:
    void userDeleteRequest(System::User user);

protected slots:
    void setupUi();
    void editButtonClickEvent(bool checked);
    void removeButtonClickEvent(bool checked);

private:
    System::User m_user;

    QVBoxLayout *m_centralLayout = nullptr;

    QLabel *m_iconLabel = nullptr;
    QLabel *m_userNameLabel = nullptr;
    QLabel *m_userSourceLabel = nullptr;
    QLabel *m_userCreatedLabel = nullptr;

    QWidget *m_centralWidget = nullptr;

    QToolButton *m_editButton = nullptr;
    QToolButton *m_deleteButton = nullptr;
};

#endif // PRINTERUSERCARD_H
