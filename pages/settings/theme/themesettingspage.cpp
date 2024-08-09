#include "themesettingspage.h"
#include "ui_themesettingspage.h"

using namespace QSourceHighlite;

ThemeSettingsPage::ThemeSettingsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThemeSettingsPage)
{
    ui->setupUi(this);

    QGridLayout *layout = (QGridLayout*)ui->footerWidget->layout();

    QPixmap pixmap = Settings::getThemeIcon("cancel-icon").pixmap(32,32);
    m_cancelButton = new QIconButton(ui->footerWidget);
    m_cancelButton->setFixedSize(250, 50);
    m_cancelButton->setText("Cancel");
    m_cancelButton->setPixmap(pixmap);
    layout->addWidget(m_cancelButton,0,0);

    m_footerSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Ignored);
    layout->addItem(m_footerSpacer,0,1);

    pixmap = Settings::getThemeIcon("accept-icon").pixmap(32,32);
    m_acceptButton = new QIconButton(ui->footerWidget);
    m_acceptButton->setFixedSize(250, 50);
    m_acceptButton->setText("Accept");
    m_acceptButton->setPixmap(pixmap);
    layout->addWidget(m_acceptButton,0,2);

    ui->variableTableWidget->setColumnCount(2);

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

    ui->codeBlockLineEdit->setText(Settings::get("theme-highlight-block").toString());
    ui->codeBuiltInLineEdit->setText(Settings::get("theme-highlight-builtin").toString());
    ui->codeCommentLineEdit->setText(Settings::get("theme-highlight-comment").toString());
    ui->codeKeywordLineEdit->setText(Settings::get("theme-highlight-keyword").toString());
    ui->codeOtherLineEdit->setText(Settings::get("theme-highlight-other").toString());
    ui->codeStringLineEdit->setText(Settings::get("theme-highlight-string").toString());
    ui->codeTypeLineEdit->setText(Settings::get("theme-highlight-type").toString());
    ui->codeNumberLineEdit->setText(Settings::get("theme-highlight-numerical").toString());

    ui->graphBackgroundEndEdit->setText(Settings::get("theme-graph-background-end").toString());
    ui->graphBackgroundStartEdit->setText(Settings::get("theme-graph-background-start").toString());
    ui->plotBackgroundStartEdit->setText(Settings::get("theme-graph-plot-background-start").toString());
    ui->plotBackgroundEndEdit->setText(Settings::get("theme-graph-plot-background-end").toString());
    ui->plotForegroundEdit->setText(Settings::get("theme-graph-plot-foreground").toString());

    bool graphAnimations = Settings::get("theme-graph-animations-enabled").toBool();
    ui->enableGraphAnimations->setChecked(graphAnimations);

    QVariableStyleSheet sheet = Settings::theme();
    QStringList variableKeys = sheet.variables().keys();
    ui->qssEdit->setText(sheet.rawStyleSheet());

    ui->variableTableWidget->clear();

    foreach(QString key, variableKeys)
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsEditable);
        item->setText(key);

        QTableWidgetItem *itemValue = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsEditable);
        itemValue->setText(sheet.variables()[key]);

        int row = ui->variableTableWidget->rowCount();

        ui->variableTableWidget->insertRow(row);
        ui->variableTableWidget->setItem(row, 0, item);
        ui->variableTableWidget->setItem(row, 1, itemValue);
    }
}

void ThemeSettingsPage::apply()
{
    Settings::set("theme-highlight-block", ui->codeBlockLineEdit->text());
    Settings::set("theme-highlight-builtin", ui->codeBuiltInLineEdit->text());
    Settings::set("theme-highlight-comment", ui->codeCommentLineEdit->text());
    Settings::set("theme-highlight-keyword", ui->codeKeywordLineEdit->text());
    Settings::set("theme-highlight-other", ui->codeOtherLineEdit->text());
    Settings::set("theme-highlight-string", ui->codeStringLineEdit->text());
    Settings::set("theme-highlight-type", ui->codeTypeLineEdit->text());
    Settings::set("theme-highlight-numerical", ui->codeNumberLineEdit->text());

    Settings::set("theme-graph-background-end", ui->graphBackgroundEndEdit->text());
    Settings::set("theme-graph-background-start", ui->graphBackgroundStartEdit->text());
    Settings::set("theme-graph-plot-background-start", ui->plotBackgroundStartEdit->text());
    Settings::set("theme-graph-plot-background-end", ui->plotBackgroundEndEdit->text());
    Settings::set("theme-graph-plot-foreground", ui->plotForegroundEdit->text());
    Settings::set("theme-graph-animations-enabled", QVariant(ui->enableGraphAnimations->isChecked()).toString());
}
