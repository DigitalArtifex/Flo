#ifndef PRINTERUPDATEITEM_H
#define PRINTERUPDATEITEM_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>

#include "ui/list/qanimatedlistitem.h"
#include "types/system.h"

class PrinterUpdateItem : public QAnimatedListItem
{
    Q_OBJECT
public:
    explicit PrinterUpdateItem(QString name, System::UpdateState::PackageState state, QWidget *parent = nullptr);

    System::UpdateState::PackageState packageState() const;
    void setPackageState(const System::UpdateState::PackageState &newPackageState);

    QString title() const;
    void setTitle(const QString &newTitle);

signals:
    void updateRequested(PrinterUpdateItem *item);

protected slots:
    void updateActionTriggered(bool checked);
    void updateButtonClickEvent();
    void setupUi();

private:
    System::UpdateState::PackageState m_packageState;

    QString m_title;

    QToolButton *m_updateButton = nullptr;

    //UI Elements
    QLabel *m_titleLabel = nullptr;
    QLabel *m_versionLabel = nullptr;
    QLabel *m_branchLabel = nullptr;
    QLabel *m_iconLabel = nullptr;

    QWidget *m_iconContainer = nullptr;

    QGridLayout *m_layout = nullptr;
    QSpacerItem *m_spacer = nullptr;

    //Context menu
    QAction *m_updateAction = nullptr;
};

#endif // PRINTERUPDATEITEM_H
