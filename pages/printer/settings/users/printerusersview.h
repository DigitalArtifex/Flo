#ifndef PRINTERUSERSVIEW_H
#define PRINTERUSERSVIEW_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QToolButton>
#include <QSpacerItem>

#include "editor/printerusereditor.h"
#include "printerusercard.h"

#include "ui/common/cardwidget/cardwidget.h"
#include "ui/QIconButton/qiconbutton.h"

#include <QKlipper/qklipper.h>

class PrinterUsersView : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterUsersView(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterUsersView();

signals:

protected slots:
    void setupUi();
    void userListChangedEvent();
    void addUserButtonClickedEvent(bool checked);

    void on_userDeleteRequest(QKlipperUser user);

private:
    QKlipperInstance *m_instnace = nullptr;
    QMap<QString, PrinterUserCard*> m_userCards;

    QHBoxLayout *m_centralLayout = nullptr;
    QWidget *m_centralWidget = nullptr;
    QSpacerItem *m_spacer = nullptr;

    QToolButton *m_addUserButton = nullptr;
};

#endif // PRINTERUSERSVIEW_H
