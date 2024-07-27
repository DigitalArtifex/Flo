#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QObject>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QMovie>
#include <QStyle>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~Dialog();

    void showLoadingScreen();
    void hideLoadingScreen();
    bool isLoadingScreenVisible();

protected:
    virtual void resizeEvent(QResizeEvent *event);

private:

    QFrame *m_loadingFrame = nullptr;
    QVBoxLayout *m_loadingFrameLayout = nullptr;
    QLabel *m_loadingFrameIcon = nullptr;
    QLabel *m_loadingFrameText = nullptr;
    QMovie *m_loadingFrameMovie = nullptr;

    QSpacerItem *m_loadingFrameTopSpacer = nullptr;
    QSpacerItem *m_loadingFrameBottomSpacer = nullptr;
};

#endif // DIALOG_H
