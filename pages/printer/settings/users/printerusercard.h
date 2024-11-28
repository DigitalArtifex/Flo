#ifndef PRINTERUSERCARD_H
#define PRINTERUSERCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "ui/common/cardwidget/cardwidget.h"

#include <QKlipper/qklipper.h>

class PrinterUserCard : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterUserCard(QKlipperUser user, QWidget *parent = nullptr);
    ~PrinterUserCard();

    QKlipperUser user() const;

    virtual void setStyleSheet(const QString &styleSheet);

public slots:
    void setUser(const QKlipperUser &user);

signals:
    void userDeleteRequest(QKlipperUser user);

protected slots:
    void setupUi();
    void editButtonClickEvent(bool checked);
    void removeButtonClickEvent(bool checked);

private:
    QKlipperUser m_user;

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
