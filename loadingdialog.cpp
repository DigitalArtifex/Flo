#include "loadingdialog.h"
#include "ui_loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDialog)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    connect(Flo::instance(),SIGNAL(loadingFinished()),this,SLOT(on_flo_loadingFinished()));
    connect(Flo::instance(),SIGNAL(loadingProgress(QString,qreal)),this,SLOT(on_flo_loadingProgress(QString,qreal)));

    _loadingGif = new QMovie(":/images/images/loading 2.gif");
    ui->loadingLabel->setMovie(_loadingGif);

    _loadingGif->start();
}

LoadingDialog::~LoadingDialog()
{
    delete ui;
}

void LoadingDialog::setMainWindow(MainWindow *window)
{
    _window = window;
}

void LoadingDialog::on_flo_loading()
{

}

void LoadingDialog::on_flo_loadingProgress(QString message, qreal progress)
{
    ui->messageLabel->setText(message);
    ui->progressBar->setValue(progress);
}

void LoadingDialog::on_flo_loadingFinished()
{
    close();
}
