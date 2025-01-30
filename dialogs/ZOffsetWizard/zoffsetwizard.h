#ifndef ZOFFSETWIZARD_H
#define ZOFFSETWIZARD_H

#include <QWizard>
#include <QKliiper/qklipper.h>

namespace Ui {
class ZOffsetWizard;
}

class ZOffsetWizard : public QWizard
{
    Q_OBJECT

public:
    explicit ZOffsetWizard(QKlipperInstance *instance, QWidget *parent = nullptr);
    ~ZOffsetWizard();

    virtual bool validateCurrentPage() override;

private slots:
    void on_ZOffsetWizard_currentIdChanged(int id);
    void showErrorMessage(QString message);
    void goToHome();
    void onHomingStarted();
    void onHomingFinished();
    bool moveToolhead(qreal amount);
    bool saveOffset();

    void on_up0025Button_clicked();

    void on_up005Button_clicked();

    void on_up010Button_clicked();

    void on_up10Button_clicked();

    void on_down0025Button_clicked();

    void on_down005Button_clicked();

    void on_down010Button_clicked();

    void on_down10Button_clicked();

    void on_up050Button_clicked();

    void on_down050Button_clicked();

    void on_ZOffsetWizard_finished(int result);

private:
    Ui::ZOffsetWizard *ui;

    bool m_homingStarted = false;
    bool m_homingFinished = false;
    bool m_wizardStarted = false;

    QKlipperInstance *m_instance = nullptr;

    qreal m_offsetValue = 0.0;
};

#endif // ZOFFSETWIZARD_H
