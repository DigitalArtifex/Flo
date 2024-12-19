#ifndef POSITIONDIALOG_H
#define POSITIONDIALOG_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QDoubleSpinBox>

#include <ui/QIconButton/qiconbutton.h>
#include <ui/common/dialog/dialog.h>


class PositionDialog : public Dialog
{
        Q_OBJECT
    public:
        explicit PositionDialog(QWidget *parent = nullptr);

        qreal x() const;

        qreal y() const;

        qreal z() const;

    public slots:
        void setX(qreal x);

        void setY(qreal y);

        void setZ(qreal z);

    signals:

        void xChanged();

        void yChanged();

        void zChanged();

    protected slots:
        void setupUi();

    private:
        QGridLayout *m_centralLayout = nullptr;

        QWidget *m_footerWidget = nullptr;
        QIconButton *m_applyButton = nullptr;
        QIconButton *m_cancelButton = nullptr;

        QGroupBox *m_xGroupBox = nullptr;
        QDoubleSpinBox *m_xSpinBox = nullptr;
        QLabel *m_xUnitLabel = nullptr;

        QGroupBox *m_yGroupBox = nullptr;
        QDoubleSpinBox *m_ySpinBox = nullptr;
        QLabel *m_yUnitLabel = nullptr;

        QGroupBox *m_zGroupBox = nullptr;
        QDoubleSpinBox *m_zSpinBox = nullptr;
        QLabel *m_zUnitLabel = nullptr;

        qreal m_x = 0;
        qreal m_y = 0;
        qreal m_z = 0;

        Q_PROPERTY(qreal x READ x WRITE setX NOTIFY xChanged FINAL)
        Q_PROPERTY(qreal y READ y WRITE setY NOTIFY yChanged FINAL)
        Q_PROPERTY(qreal z READ z WRITE setZ NOTIFY zChanged FINAL)
};

#endif // POSITIONDIALOG_H
