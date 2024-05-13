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

        qreal fadeEnd = 0;
        qreal fadeStart = 0;
        qreal fadeTarget = 0;
        qreal horizontalMoveZ = 0;
        qreal adaptiveMargin = 0;
        qreal speed = 0;
        qreal tension = 0;
        qreal splitDeltaZ = 0;
        qreal moveCheckDistance = 0;

        QString profileName;
        QStringList profiles;

        Limit minimum;
        Limit maximum;
        Limit probeCount;

        QList<QList<qreal>> matrix;
        QList<QList<qreal>> probed;

        QString algorithm;
    };

    /*!
     * \brief The AdjustmentScrew class
     */
    struct AdjustmentScrew
    {
        struct Adjustment
        {
            enum Direction
            {
                Clockwise,
                CounterClockwise
            };

            //Ratio string
            QString amount;
            QString sign;

            Direction direction;

            bool isBase = false;

            qreal z = 0;
        };

        QString name;
        QString thread;

        QPair<qreal,qreal> tiltAdjust;

        qreal speed;

        Adjustment adjustment;
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

    AdjustmentScrew *adjustmentScrew(QString &key) const;
    void setAdjustmentScrew(QString &key, AdjustmentScrew *screw);

    bool tiltAdjustError() const;
    void setTiltAdjustError(bool tiltAdjustError);

    bool adjustmentScrewsError() const;
    void setAdjustmentScrewsError(bool adjustmentScrewsError);

    qreal adjustmentScrewsMaxDeviation() const;
    void setAdjustmentScrewsMaxDeviation(qreal adjustmentScrewsMaxDeviations);

signals:
    void meshUpdated(Q3DPrintBed *bed);
    void adjustmentScrewsUpdated(Q3DPrintBed *bed);

private:
    qreal _currentTemp = 0;
    qreal _targetTemp = 0;
    qreal _power = 0;
    qreal _watts = 0;

    QDateTime _startTime;

    Mesh _bedMesh;

    QMap<QString, AdjustmentScrew*> _adjustmentScrews;
    bool                            _adjustmentScrewsError;
    qreal                           _adjustmentScrewsMaxDeviation;

    bool                            _tiltAdjustError;
};

#endif // BED_H
