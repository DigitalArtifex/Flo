#ifndef BED_H
#define BED_H

#include <QObject>
#include <QDateTime>

#include <QPair>

class Q3DPrintBed : public QObject
{
    Q_OBJECT
public:
    enum Type
    {
        Heated,
        NonHeated
    };

    struct Mesh
    {
        struct Limit
        {
            qreal x;
            qreal y;
        };

        QString profileName;
        QStringList profiles;

        Limit minimum;
        Limit maximum;

        QList<QList<qreal>> matrix;
        QList<QList<qreal>> probed;
    };

    Q3DPrintBed(Type type = NonHeated, QObject *parent = nullptr);

    long timeRunning();
    qreal currentTemp() const;
    void setCurrentTemp(qreal currentTemp);

    qreal targetTemp() const;
    void setTargetTemp(qreal targetTemp);

    qreal power() const;
    void setPower(qreal power);

    qreal watts() const;
    void setWatts(qreal watts);

    Mesh bedMesh() const;
    void setBedMesh(const Mesh &bedMesh);

signals:
    void meshUpdated(Q3DPrintBed *bed);

private:
    qreal _currentTemp = 0;
    qreal _targetTemp = 0;
    qreal _power = 0;
    qreal _watts = 0;

    QDateTime _startTime;

    Mesh _bedMesh;
};

#endif // BED_H
