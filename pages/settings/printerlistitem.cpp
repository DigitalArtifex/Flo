#include "printerlistitem.h"
#include "ui_printerlistitem.h"

PrinterListItem::PrinterListItem(QWidget *parent) :
    QFrame(parent),
    QListWidgetItem(),
    ui(new Ui::PrinterListItem)
{
    ui->setupUi(this);
    setUiClasses();
    this->setProperty("pressed", false);
    this->setProperty("selected", false);
}

PrinterListItem::~PrinterListItem()
{
    delete ui;
}

void PrinterListItem::setPrinterDefinition(PrinterDefinition definition)
{
    m_definition = definition;
    ui->printerName->setText(m_definition.name);
    ui->instanceLocation->setText(m_definition.instanceLocation);

    if(definition.defaultPrinter)
        ui->defaultLabel->setText(QString("Default Printer: Yes"));
    else
        ui->defaultLabel->setText(QString("Default Printer: No"));

    if(definition.autoConnect)
        ui->autoConnectLabel->setText(QString("Auto Connect: Yes"));
    else
        ui->autoConnectLabel->setText(QString("Auto Connect: No"));
}

void PrinterListItem::setUiClasses()
{
    ui->printerName->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItemName" ));
    ui->autoConnectLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItemInfo" ));
    ui->defaultLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItemInfo" ));
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItem" ));
}

void PrinterListItem::setSelected(bool selected)
{
    this->setProperty("pressed", selected);
    this->setProperty("selected", selected);
    this->style()->polish(this);
    this->update();
}

bool PrinterListItem::selected()
{
    return this->property("selected").toBool();
}

PrinterDefinition PrinterListItem::printerDefinition()
{
    return m_definition;
}

void PrinterListItem::clickTimeout()
{
    if(this->m_pressed)
        this->m_longPress = true;
}

void PrinterListItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->m_clickTimer = new QTimer(this);
        this->m_clickTimer->setInterval(500);
        this->m_clickTimer->setSingleShot(true);
        connect(this->m_clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
        this->m_clickTimer->start();
        this->setProperty("pressed", true);
        m_pressed = true;
        this->style()->polish(this);
        qDebug() << "Pressed";
    }
}

void PrinterListItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->setProperty("pressed", false);
        this->setProperty("selected", true);
        this->style()->polish(this);
        qDebug() << "Released";

        if(this->m_clickTimer != NULL)
        {
            m_clickTimer->stop();
            disconnect(this->m_clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
            delete m_clickTimer;
            m_clickTimer = NULL;
        }

        if(m_pressed && !m_longPress)
        {
            m_pressed = false;
            m_longPress = false;
            emit(clicked(this));
        }
        else if(m_longPress)
        {
            m_pressed = false;
            m_longPress = false;
            emit(longPressed(this));
        }
    }
}
