#include "loadingpage.h"
#include "ui_loadingpage.h"

LoadingPage::LoadingPage(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LoadingPage)
{
    ui->setupUi(this);
}

LoadingPage::~LoadingPage()
{
    delete ui;
}
