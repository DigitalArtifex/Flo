#ifndef THEMESETTINGSPAGE_H
#define THEMESETTINGSPAGE_H

#include <QWidget>
#include "system/settings.h"
#include "ui/QIconButton/qiconbutton.h"

#include "QSourceHighlite/qsourcehighliter.h"

namespace Ui {
class ThemeSettingsPage;
}

class ThemeSettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeSettingsPage(QWidget *parent = nullptr);
    ~ThemeSettingsPage();

    void reset();
    void apply();

private:
    Ui::ThemeSettingsPage *ui;

    QIconButton *m_acceptButton = nullptr;
    QIconButton *m_cancelButton = nullptr;
    QSpacerItem *m_footerSpacer = nullptr;

    QSourceHighlite::QSourceHighliter *m_highlighter;
};

#endif // THEMESETTINGSPAGE_H
