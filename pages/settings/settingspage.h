#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QFrame>
#include <QParallelAnimationGroup>
#include <QMessageBox>

#include "edit_printer/editprinterdialog.h"
#include "printerlistwidget.h"

#include "qpropertyanimation.h"
#include "theme/themesettingspage.h"
#include "system/systemsettingspage.h"

#include "QSourceHighlite/qsourcehighliter.h"

using namespace QSourceHighlite;

namespace Ui {
class SettingsPage;
}

class SettingsPage : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);
    ~SettingsPage();

    void updatePrinterList();

    void reset();
    void apply();

public slots:
    virtual void setStyleSheet(const QString &styleSheet);

signals:
    void printerAdded(QKlipperInstance *definition);

protected slots:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void showEvent(QShowEvent *event);

private slots:
    void printerListWidgetItemSelectedEvent(PrinterListItem *item);

    void editPrinterButtonClickEvent();
    void addPrinterButtonClickEvent();
    void removePrinterButtonClickEvent();

    void printersActionButtonClickEvent();
    void themeActionButtonClickEvent();
    void systemActionButtonClickEvent();

    void onResetButtonClicked();
    void onCancelButtonClicked();
    void onApplyButtonClicked();

    void hideFooter();
    void showFooter();
    void setupAnimations();
    void onFooterAnimationFinished();
    void setupIcons();

private:
    Ui::SettingsPage *ui;

    QPropertyAnimation *m_footerAnimation = nullptr;
    bool                m_isFooterShown = true;
    QRect               m_footerInGeometry;
    QRect               m_footerOutGeometry;

    QPropertyAnimation *m_pageAnimation = nullptr;

    QParallelAnimationGroup *m_footerAnimationGroup = nullptr;

    QPropertyAnimation *m_pageInAnimation = nullptr;
    QPropertyAnimation *m_pageOutAnimation = nullptr;

    EditPrinterDialog *m_editPrinterDialog = nullptr;
    PrinterListWidget *m_printerListWidget = nullptr;

    ThemeSettingsPage *m_themeSettingsPage = nullptr;
    SystemSettingsPage *m_systemSettingsPage = nullptr;

    QIconButton *m_addPrinterButton = nullptr;
    QIconButton *m_editPrinterButton = nullptr;
    QIconButton *m_removePrinterButton = nullptr;

    QIconButton *m_printersActionButton = nullptr;
    QIconButton *m_themeActionButton = nullptr;
    QIconButton *m_systemActionButton = nullptr;

    QIconButton *m_acceptButton = nullptr;
    QIconButton *m_cancelButton = nullptr;
    QIconButton *m_resetButton = nullptr;
    QSpacerItem *m_footerSpacer = nullptr;
};

#endif // SETTINGSPAGE_H
