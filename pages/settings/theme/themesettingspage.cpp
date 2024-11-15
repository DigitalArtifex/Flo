#include "themesettingspage.h"
#include "ui_themesettingspage.h"

using namespace QSourceHighlite;

ThemeSettingsPage::ThemeSettingsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThemeSettingsPage)
{
    ui->setupUi(this);

    ui->variableTableWidget->setColumnCount(3);

    m_highlighter = new QSourceHighliter(ui->qssEdit->document());
    m_highlighter->setCurrentLanguage(QSourceHighliter::CodeCSS);
    m_highlighter->setTheme(QSourceHighliter::System);

    reset();
}

ThemeSettingsPage::~ThemeSettingsPage()
{
    delete ui;
}

void ThemeSettingsPage::reset()
{
    for(int i = ui->variableTableWidget->rowCount(); i >= 0; --i)
        ui->variableTableWidget->removeRow(i);

    ui->codeBlockLineEdit->setText(Settings::get("theme/highlight-block").toString());
    ui->codeBuiltInLineEdit->setText(Settings::get("theme/highlight-builtin").toString());
    ui->codeCommentLineEdit->setText(Settings::get("theme/highlight-comment").toString());
    ui->codeKeywordLineEdit->setText(Settings::get("theme/highlight-keyword").toString());
    ui->codeOtherLineEdit->setText(Settings::get("theme/highlight-other").toString());
    ui->codeStringLineEdit->setText(Settings::get("theme/highlight-string").toString());
    ui->codeTypeLineEdit->setText(Settings::get("theme/highlight-type").toString());
    ui->codeNumberLineEdit->setText(Settings::get("theme/highlight-numerical").toString());

    ui->graphBackgroundEndEdit->setText(Settings::get("theme/graph-background-end").toString());
    ui->graphBackgroundStartEdit->setText(Settings::get("theme/graph-background-start").toString());
    ui->plotBackgroundStartEdit->setText(Settings::get("theme/graph-plot-background-start").toString());
    ui->plotBackgroundEndEdit->setText(Settings::get("theme/graph-plot-background-end").toString());
    ui->plotForegroundEdit->setText(Settings::get("theme/graph-plot-foreground").toString());

    bool graphAnimations = Settings::get("theme/graph-animations-enabled").toBool();
    ui->enableGraphAnimations->setChecked(graphAnimations);

    for(QString theme : Settings::themeList())
    {
        theme.replace(0, 1, theme.at(0).toUpper());
        ui->themeComboBox->addItem(theme);
    }

    QVariableStyleSheet sheet = Settings::theme();
    QStringList variableKeys = sheet.variables().keys();
    ui->qssEdit->setText(sheet.rawStyleSheetBody());

    foreach(QString key, variableKeys)
    {
        addThemeVariable(key, sheet.variables()[key]);
    }
}

void ThemeSettingsPage::apply()
{
    QVariableStyleSheet sheet = Settings::theme();

    sheet.setValue("highlight-block", ui->codeBlockLineEdit->text());
    sheet.setValue("highlight-builtin", ui->codeBuiltInLineEdit->text());
    sheet.setValue("highlight-comment", ui->codeCommentLineEdit->text());
    sheet.setValue("highlight-keyword", ui->codeKeywordLineEdit->text());
    sheet.setValue("highlight-other", ui->codeOtherLineEdit->text());
    sheet.setValue("highlight-string", ui->codeStringLineEdit->text());
    sheet.setValue("highlight-type", ui->codeTypeLineEdit->text());
    sheet.setValue("highlight-numerical", ui->codeNumberLineEdit->text());

    sheet.setValue("graph-background-end", ui->graphBackgroundEndEdit->text());
    sheet.setValue("graph-background-start", ui->graphBackgroundStartEdit->text());
    sheet.setValue("graph-plot-background-start", ui->plotBackgroundStartEdit->text());
    sheet.setValue("graph-plot-background-end", ui->plotBackgroundEndEdit->text());
    sheet.setValue("graph-plot-foreground", ui->plotForegroundEdit->text());
    sheet.setValue("graph-animations-enabled", QVariant(ui->enableGraphAnimations->isChecked()).toString());

    for(int i = 0; i < ui->variableTableWidget->rowCount(); i++)
    {
        QTableWidgetItem *nameItem = ui->variableTableWidget->item(i, 0);
        QTableWidgetItem *valueItem = ui->variableTableWidget->item(i, 1);

        sheet.setValue(nameItem->text(), valueItem->text());
    }

    sheet.setRawStyleSheetBody(ui->qssEdit->toPlainText());

    QString theme = ui->themeComboBox->currentText();
    theme.replace(0, 1, theme.at(0).toLower());

    Settings::saveTheme(theme, sheet);
}

void ThemeSettingsPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    int width = ui->variableTableWidget->viewport()->frameSize().width();
    width -= ui->variableTableWidget->columnWidth(1);
    width -= 50;

    ui->variableTableWidget->setColumnWidth(0, width);
    ui->variableTableWidget->setColumnWidth(2, 50);
}

void ThemeSettingsPage::on_themeVariableResetButton_clicked()
{
    ui->themeVariableNameEdit->setText("");
    ui->themeVariableValueEdit->setText("");
}


void ThemeSettingsPage::on_themeVariableAddButton_clicked()
{
    addThemeVariable(ui->themeVariableNameEdit->text(), ui->themeVariableValueEdit->text());
    ui->themeVariableNameEdit->setText("");
    ui->themeVariableValueEdit->setText("");
}

void ThemeSettingsPage::addThemeVariable(const QString &name, const QString &value)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(name);

    QTableWidgetItem *itemValue = new QTableWidgetItem();
    //itemValue->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
    itemValue->setText(value);

    QTableWidgetItem *itemDelete = new QTableWidgetItem();
    itemDelete->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    itemDelete->setIcon(Settings::getThemeIcon("delete-icon"));

    int row = ui->variableTableWidget->rowCount();

    ui->variableTableWidget->insertRow(row);
    ui->variableTableWidget->setItem(row, 0, item);
    ui->variableTableWidget->setItem(row, 1, itemValue);
    ui->variableTableWidget->setItem(row, 2, itemDelete);
}

void ThemeSettingsPage::on_variableTableWidget_cellDoubleClicked(int row, int column)
{
    if(column == 2)
        ui->variableTableWidget->removeRow(row);
}

