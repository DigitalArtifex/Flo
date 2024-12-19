#ifndef PRINTERFANITEM_H
#define PRINTERFANITEM_H

#include <QObject>
#include <QQmlEngine>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include <QKlipper/qklipper.h>

class PrinterFanItem : public QWidget
{
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit PrinterFanItem(QKlipperFan *fan, QWidget *parent = nullptr);

    signals:

    protected slots:
        void onFanSpeedChanged();
        void onFanNameChanged();

    protected:
        void setupUi();
        virtual void changeEvent(QEvent *event) override;

    private:
        QHBoxLayout *m_centralLayout = nullptr;
        QLabel *m_iconLabel = nullptr;
        QLabel *m_nameLabel = nullptr;
        QLabel *m_speedLabel = nullptr;

        QKlipperFan *m_fan;
};

#endif // PRINTERFANITEM_H
