#include "themesettingspage.h"
#include "ui_themesettingspage.h"

using namespace QSourceHighlite;

ThemeSettingsPage::ThemeSettingsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThemeSettingsPage)
{
    ui->setupUi(this);

    ui->variableTableWidget->setColumnCount(3);
    ui->variableTableWidget->setVerticalHeaderLabels(QStringList {"Name", "Value", "Delete"});
    ui->variableTableWidget->verticalHeader()->setMinimumSectionSize(50);

    m_highlighter = new QSourceHighliter(ui->qssEdit->document());
    m_highlighter->setCurrentLanguage(QSourceHighliter::CodeCSS);
    m_highlighter->setTheme(QSourceHighliter::System);
    setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));
    ui->scrollAreaWidgetContents_2->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "Page"));

    reset();
}

ThemeSettingsPage::~ThemeSettingsPage()
{
    delete ui;
}

void ThemeSettingsPage::reset()
{
    ui->themeComboBox->clear();

    int index = 0;
    bool indexFound = false;

    for(QString &theme : Settings::themeList())
    {
        QString displayName = theme;
        displayName.replace(0, 1, displayName.at(0).toUpper());

        ui->themeComboBox->addItem(displayName, theme);

        if(theme == Settings::currentThemeName())
        {
            indexFound = true;
            index = ui->themeComboBox->count() - 1;
        }
    }

    if(indexFound)
        ui->themeComboBox->setCurrentIndex(index);

    ui->iconSetSelector->clear();

    index = 0;
    indexFound = false;

    for(QString &iconSet : Settings::getIconSetList())
    {
        QString displayName = iconSet;
        displayName.replace(0, 1, displayName.at(0).toUpper());

        ui->iconSetSelector->addItem(displayName, iconSet);

        if(iconSet == Settings::currentIconSetName())
        {
            indexFound = true;
            index = ui->iconSetSelector->count() - 1;
        }
    }

    if(indexFound)
        ui->iconSetSelector->setCurrentIndex(index);
}

void ThemeSettingsPage::apply()
{
    QVariableStyleSheet sheet;

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

    if(ui->iconSetSelector->currentData() != Settings::currentIconSetName())
        Settings::setIconSet(ui->iconSetSelector->currentData().toString());

    Settings::saveTheme(ui->themeComboBox->currentData().toString(), sheet);
    Settings::setTheme(ui->themeComboBox->currentData().toString());
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
    item->setSizeHint(QSize(32,32));

    QTableWidgetItem *itemValue = new QTableWidgetItem();
    //itemValue->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable);
    itemValue->setText(value);
    itemValue->setSizeHint(QSize(32,32));

    QTableWidgetItem *itemDelete = new QTableWidgetItem();
    itemDelete->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    itemDelete->setIcon(Settings::getThemeIcon("delete"));
    itemDelete->setSizeHint(QSize(32,32));

    int row = ui->variableTableWidget->rowCount();

    ui->variableTableWidget->insertRow(row);
    ui->variableTableWidget->setRowHeight(row, 32);
    ui->variableTableWidget->setItem(row, 0, item);
    ui->variableTableWidget->setItem(row, 1, itemValue);
    ui->variableTableWidget->setItem(row, 2, itemDelete);
}

void ThemeSettingsPage::on_variableTableWidget_cellDoubleClicked(int row, int column)
{
    if(column == 2)
        ui->variableTableWidget->removeRow(row);
}


void ThemeSettingsPage::on_iconSetSelector_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
}

void ThemeSettingsPage::on_deleteThemeButton_clicked()
{
    if(Settings::deleteTheme(ui->themeComboBox->currentData().toString()))
    {
        int index = ui->themeComboBox->currentIndex();
        ui->themeComboBox->setCurrentIndex(0);
        ui->themeComboBox->removeItem(index);
    }
}

void ThemeSettingsPage::resetThemeData()
{
    qDebug() << "Theme" << ui->themeComboBox->currentData().toString();

    QVariableStyleSheet sheet = Settings::getThemeSheet(ui->themeComboBox->currentData().toString());

    for(int i = ui->variableTableWidget->rowCount(); i >= 0; --i)
        ui->variableTableWidget->removeRow(i);

    ui->codeBlockLineEdit->setText(sheet.variables()["highlight-block"]);
    ui->codeBuiltInLineEdit->setText(sheet.variables()["highlight-builtin"]);
    ui->codeCommentLineEdit->setText(sheet.variables()["highlight-comment"]);
    ui->codeKeywordLineEdit->setText(sheet.variables()["highlight-keyword"]);
    ui->codeOtherLineEdit->setText(sheet.variables()["highlight-other"]);
    ui->codeStringLineEdit->setText(sheet.variables()["highlight-string"]);
    ui->codeTypeLineEdit->setText(sheet.variables()["highlight-type"]);
    ui->codeNumberLineEdit->setText(sheet.variables()["highlight-numerical"]);

    ui->graphBackgroundEndEdit->setText(sheet.variables()["graph-background-end"]);
    ui->graphBackgroundStartEdit->setText(sheet.variables()["graph-background-start"]);
    ui->plotBackgroundStartEdit->setText(sheet.variables()["graph-plot-background-start"]);
    ui->plotBackgroundEndEdit->setText(sheet.variables()["graph-plot-background-end"]);
    ui->plotForegroundEdit->setText(sheet.variables()["graph-plot-foreground"]);

    QStringList variableKeys = sheet.variables().keys();
    ui->qssEdit->setText(sheet.rawStyleSheetBody());

    for(QString &key : variableKeys)
        addThemeVariable(key, sheet.variables()[key]);

    ui->qssEdit->setText(sheet.stylesheet());
}

void ThemeSettingsPage::on_themeComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index)

    if(ui->themeComboBox->currentData().isValid())
        resetThemeData();

    if(ui->themeComboBox->currentData().toString() != "default")
    {
        ui->deleteThemeButton->setEnabled(true);
        //ui->themeComboBox->setEditable(true);
    }
    else
    {
        ui->deleteThemeButton->setEnabled(false);
        //ui->themeComboBox->setEditable(false);
    }
}

void ThemeSettingsPage::on_copyThemeButton_clicked()
{
    QVariableStyleSheet sheet;

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

    QString name = ui->themeComboBox->currentText();

    QRegularExpression copyExpression("_copy\\d{0,}$");
    QRegularExpressionMatch copyMatch = copyExpression.match(name);

    if(copyMatch.hasMatch())
    {
        QString match = copyMatch.captured();
        match.remove("_copy");
        name.remove(copyExpression);

        bool okay = false;
        int number = match.toInt(&okay);

        if(!okay)
            number = 1;
        else
            number++;

        name.append(QString("_copy%1").arg(number));
    }
    else
        name.append("_copy");

    Settings::saveTheme(name.toLower(), sheet);
    ui->themeComboBox->addItem(name, name.toLower());
    ui->themeComboBox->setCurrentIndex(ui->themeComboBox->count() - 1);
}

void ThemeSettingsPage::setIcons()
{
    ui->copyThemeButton->setIcon(Settings::getThemeIcon("copy"));
    ui->deleteThemeButton->setIcon(Settings::getThemeIcon("delete"));
}

void ThemeSettingsPage::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::StyleChange)
        setIcons();
}
