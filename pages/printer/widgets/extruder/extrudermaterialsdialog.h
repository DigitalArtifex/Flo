#ifndef EXTRUDERMATERIALSDIALOG_H
#define EXTRUDERMATERIALSDIALOG_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QDoubleSpinBox>

#include <ui/common/dialog/dialog.h>
#include <ui/QIconButton/qiconbutton.h>

class ExtruderMaterialsDialog : public Dialog
{
        Q_OBJECT
        QML_ELEMENT
    public:
        enum MaterialDirection
        {
            None,
            MaterialExtrude,
            MaterialRetract
        };

        explicit ExtruderMaterialsDialog(QWidget *parent = nullptr);

        MaterialDirection materialDirection() const;

        qreal distance() const;

        qreal speed() const;

    public slots:
        void setMaterialDirection(MaterialDirection materialDirection);

        void setDistance(qreal distance);

        void setSpeed(qreal speed);

    signals:

        void materialDirectionChanged();

        void distanceChanged();

        void speedChanged();

    protected:
        virtual void changeEvent(QEvent *event) override;

    private slots:
        void setupUi();
        void setupIcons();

    private:
        QGridLayout *m_centralLayout = nullptr;

        QWidget *m_footerWidget = nullptr;
        QIconButton *m_extrudeButton = nullptr;
        QIconButton *m_cancelButton = nullptr;

        QGroupBox *m_distanceGroupBox = nullptr;
        QDoubleSpinBox *m_distanceSpinBox = nullptr;
        QLabel *m_distanceUnitLabel = nullptr;

        QGroupBox *m_speedGroupBox = nullptr;
        QDoubleSpinBox *m_speedSpinBox = nullptr;
        QLabel *m_speedUnitLabel = nullptr;

        MaterialDirection m_materialDirection = None;

        qreal m_distance = 0;
        qreal m_speed = 0;

        Q_PROPERTY(MaterialDirection materialDirection READ materialDirection WRITE setMaterialDirection NOTIFY materialDirectionChanged FINAL)
        Q_PROPERTY(qreal distance READ distance WRITE setDistance NOTIFY distanceChanged FINAL)
        Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
};

#endif // EXTRUDERMATERIALSDIALOG_H
