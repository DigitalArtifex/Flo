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

void PrinterListItem::setInstance(QKlipperInstance *instance)
{
    m_definition = instance;
    ui->printerName->setText(instance->name());
    ui->instanceLocation->setText(instance->instanceLocation());
    ui->addressLabel->setText(QString("Address: ") + m_definition->address());
    ui->portLabel->setText(QString("Port: ") + QString::number(m_definition->port()));

    if(!m_definition->thumbnail().isNull())
        ui->iconLabel->setPixmap(QPixmap::fromImage(m_definition->thumbnail()).scaled(ui->iconLabel->size()));

    connect(instance, SIGNAL(addressChanged()), this, SLOT(onAddressChanged()));
    connect(instance, SIGNAL(portChanged()), this, SLOT(onPortChanged()));
    connect(instance, SIGNAL(nameChanged()), this, SLOT(onInstanceNameChanged()));
    connect(instance, SIGNAL(thumbnailChanged()), this, SLOT(onInstanceThumbnailChanged()));
}

void PrinterListItem::setUiClasses()
{
    ui->printerName->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItemName" ));
    ui->portLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItemInfo" ));
    ui->addressLabel->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItemInfo" ));
    this->setProperty("class", QVariant::fromValue<QStringList>( QStringList() << "PrinterListItem" ));
}

void PrinterListItem::setSelected(bool selected)
{
    this->setProperty("pressed", selected);
    this->setProperty("selected", selected);

    style()->polish(this);
}

bool PrinterListItem::selected()
{
    return this->property("selected").toBool();
}

QKlipperInstance *PrinterListItem::instance()
{
    return m_definition;
}

void PrinterListItem::clickTimeout()
{
    if(this->m_pressed)
        this->m_longPress = true;
}

void PrinterListItem::onInstanceNameChanged()
{
    if(m_definition)
        ui->printerName->setText(m_definition->name());
}

void PrinterListItem::onAddressChanged()
{
    if(m_definition)
        ui->addressLabel->setText(m_definition->address());
}

void PrinterListItem::onPortChanged()
{
    if(m_definition)
        ui->portLabel->setText(QString::number(m_definition->port()));
}

void PrinterListItem::onInstanceThumbnailChanged()
{
    if(!m_definition->thumbnail().isNull())
        ui->iconLabel->setPixmap(QPixmap::fromImage(m_definition->thumbnail()).scaled(ui->iconLabel->size()));
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
        style()->polish(this);
    }
}

void PrinterListItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->setProperty("pressed", false);
        this->setProperty("selected", true);
        style()->polish(this);

        if(this->m_clickTimer != NULL)
        {
            m_clickTimer->stop();
            disconnect(this->m_clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
            m_clickTimer->deleteLater();
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
