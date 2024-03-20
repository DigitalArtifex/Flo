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
    _definition = definition;
    ui->printerName->setText(_definition.name);
    ui->instanceLocation->setText(_definition.instanceLocation);

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

void PrinterListItem::clickTimeout()
{
    if(this->_pressed)
        this->_longPress = true;
}

void PrinterListItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        this->_clickTimer = new QTimer(this);
        this->_clickTimer->setInterval(500);
        this->_clickTimer->setSingleShot(true);
        connect(this->_clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
        this->_clickTimer->start();
        this->setProperty("pressed", true);
        _pressed = true;
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

        if(this->_clickTimer != NULL)
        {
            _clickTimer->stop();
            disconnect(this->_clickTimer, SIGNAL(timeout()), this, SLOT(clickTimeout()));
            delete _clickTimer;
            _clickTimer = NULL;
        }

        if(_pressed && !_longPress)
        {
            _pressed = false;
            _longPress = false;
            emit(clicked(this));
        }
        else if(_longPress)
        {
            _pressed = false;
            _longPress = false;
            emit(longPressed(this));
        }
    }
}
