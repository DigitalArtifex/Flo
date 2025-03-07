#ifndef PIDDIALOG_H
#define PIDDIALOG_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QDoubleSpinBox>

#include <common/dialog/dialog.h>
#include <ui/QIconButton/qiconbutton.h>

class PidDialog : public Dialog
{
        Q_OBJECT
    public:
        explicit PidDialog(QWidget *parent = nullptr);

        qreal target() const;

    public slots:
        void setTarget(qreal target);

    signals:

        void targetChanged();

    protected:
        virtual void changeEvent(QEvent *event) override;

    private slots:
        void setupUi();
        void setupIcons();

    private:
        QGridLayout *m_centralLayout = nullptr;

        QWidget *m_footerWidget = nullptr;
        QIconButton *m_acceptButton = nullptr;
        QIconButton *m_rejectButton = nullptr;

        QGroupBox *m_targetGroupBox = nullptr;
        QDoubleSpinBox *m_targetSpinBox = nullptr;

        qreal m_target = 0;

        QLabel *m_pidText = nullptr;

        Q_PROPERTY(qreal target READ target WRITE setTarget NOTIFY targetChanged FINAL)
};

#endif // PIDDIALOG_H
