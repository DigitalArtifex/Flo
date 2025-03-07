#ifndef PRINTERUSERSVIEW_H
#define PRINTERUSERSVIEW_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QToolButton>
#include <QSpacerItem>

#include "editor/printerusereditor.h"
#include "printerusercard.h"

#include "common/CardWidget/cardwidget.h"
#include "ui/QIconButton/qiconbutton.h"

#include <QKlipper/qklipper.h>
#include <qwizard.h>

class PrinterUsersView : public CardWidget
{
    Q_OBJECT
public:
    explicit PrinterUsersView(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~PrinterUsersView();

signals:
    void dialogRequested(QDialog *);
    void wizardRequested(QWizard *);

protected slots:
    void setupUi();
    void userListChangedEvent();
    void addUserButtonClickedEvent(bool checked);

    void on_userDeleteRequest(QKlipperUser user);
    void onUserEditorFinished(int returnCode);

protected:
    void setIcons();
    virtual void changeEvent(QEvent *event) override;

private:
    PrinterUserEditor *m_editor = nullptr;
    QKlipperInstance *m_instnace = nullptr;
    QMap<QString, PrinterUserCard*> m_userCards;

    QHBoxLayout *m_centralLayout = nullptr;
    QWidget *m_centralWidget = nullptr;
    QSpacerItem *m_spacer = nullptr;

    QToolButton *m_addUserButton = nullptr;
};

#endif // PRINTERUSERSVIEW_H
