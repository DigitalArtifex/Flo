#ifndef THEMESETTINGSPAGE_H
#define THEMESETTINGSPAGE_H

#include <QWidget>
#include <flo/settings.h>
#include "ui/QIconButton/qiconbutton.h"

#include "3rdparty/QSourceHighlite/qsourcehighliter.h"

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

private slots:
    void on_themeVariableResetButton_clicked();
    void on_themeVariableAddButton_clicked();

    void on_variableTableWidget_cellDoubleClicked(int row, int column);

    void on_iconSetSelector_currentTextChanged(const QString &arg1);

    void on_deleteThemeButton_clicked();

    void on_themeComboBox_currentIndexChanged(int index);

    void on_copyThemeButton_clicked();

protected:
    void setIcons();
    virtual void changeEvent(QEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    void resetThemeData();
    void addThemeVariable(const QString &name, const QString &value);
    Ui::ThemeSettingsPage *ui;

    QSourceHighlite::QSourceHighliter *m_highlighter;
};

#endif // THEMESETTINGSPAGE_H
