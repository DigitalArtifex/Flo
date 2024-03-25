#ifndef LOADINGPAGE_H
#define LOADINGPAGE_H

#include <QFrame>

namespace Ui {
class LoadingPage;
}

class LoadingPage : public QFrame
{
    Q_OBJECT

public:
    explicit LoadingPage(QWidget *parent = nullptr);
    ~LoadingPage();

private:
    Ui::LoadingPage *ui;
};

#endif // LOADINGPAGE_H
