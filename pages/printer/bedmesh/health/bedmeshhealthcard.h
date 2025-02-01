#ifndef BEDMESHHEALTHCARD_H
#define BEDMESHHEALTHCARD_H

#include <QObject>
#include <QWidget>
#include <QProgressBar>
#include "ui/common/cardwidget/cardwidget.h"

#include "QKlipper/qklipper.h"
#include "../bedmeshdata.h"
#include "flo/settings.h"

class BedMeshHealthCard : public CardWidget
{
        Q_OBJECT
    public:
        BedMeshHealthCard(BedMeshData *data, QWidget *parent = nullptr);

        virtual void setStyleSheet(const QString &stylesheet);

    protected:
        void setupUi();
        void setupIcons();

    protected slots:
        void onBedMeshUpdated();

    private:
        QWidget *m_centralWidget = nullptr;
        QGridLayout *m_centralLayout = nullptr;

        QLabel *m_minLabel = nullptr;
        QLabel *m_maxLabel = nullptr;
        QLabel *m_varianceLabel = nullptr;
        QLabel *m_statusIconLabel = nullptr;

        QProgressBar *m_bedHealth = nullptr;

        BedMeshData *m_meshData = nullptr;
};

#endif // BEDMESHHEALTHCARD_H
