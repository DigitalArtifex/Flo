#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QMovie>

#include "mainwindow.h"
#include "system/flo.h"

namespace Ui {
class LoadingDialog;
}

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = nullptr);
    ~LoadingDialog();

    void setMainWindow(MainWindow *window);

private slots:

    void on_flo_loading();
    void on_flo_loadingProgress(QString message, qreal progress);
    void on_flo_loadingFinished();

private:
    Ui::LoadingDialog *ui;
    MainWindow *_window;

    QMovie *_loadingGif = nullptr;
};

#endif // LOADINGDIALOG_H
