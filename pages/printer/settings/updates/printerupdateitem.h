#ifndef PRINTERUPDATEITEM_H
#define PRINTERUPDATEITEM_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>

#include "ui/list/qanimatedlistitem.h"
#include <QKlipper/qklipper.h>

class PrinterUpdateItem : public QAnimatedListItem
{
    Q_OBJECT
public:
    explicit PrinterUpdateItem(QString name, QKlipperUpdatePackage state, QWidget *parent = nullptr);

    QKlipperUpdatePackage packageState() const;
    void setPackageState(QKlipperUpdatePackage newPackageState);

    QString title() const;
    void setTitle(const QString &newTitle);

signals:
    void updateRequested(PrinterUpdateItem *item);

protected slots:
    void updateActionTriggered(bool checked);
    void updateButtonClickEvent();
    void setupUi();

private:
    QKlipperUpdatePackage m_packageState;

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
