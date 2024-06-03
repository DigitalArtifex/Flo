#ifndef BED_H
#define BED_H

#include <QObject>
#include <QDateTime>

#include <QPair>

class Printer;

class Q3DPrintBed : public QObject
{
    Q_OBJECT

    friend class QAbstractKlipperConsole;
    friend class Printer;
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

            Direction direction = Clockwise;

            bool isBase = false;

            qreal z = 0;
        };

        QString name;
        QString thread;

        QPair<qreal,qreal> tiltAdjust;

        qreal speed;

        Adjustment adjustment;
    };

    Q3DPrintBed(Printer *printer, Type type = NonHeated, QObject *parent = nullptr);

    long timeRunning();
    qreal currentTemp() const;

    qreal targetTemp() const;

    qreal power() const;

    qreal watts() const;

    Mesh bedMesh() const;

    AdjustmentScrew *adjustmentScrew(QString &key) const;

    bool tiltAdjustError() const;

    bool adjustmentScrewsError() const;

    qreal adjustmentScrewsMaxDeviation() const;

    QMap<QString, AdjustmentScrew *> adjustmentScrews() const;

    bool hasAdjustmentScrewResult() const;

    void calibrateAdjustmentScrews();
    void calibrateBedMesh();

    Printer *printer() const;
    void setPrinter(Printer *printer);

    void setWatts(qreal watts);

    Type type() const;

signals:
    void meshUpdated(Q3DPrintBed *bed);
    void adjustmentScrewsUpdated(Q3DPrintBed *bed);
    void updated(Q3DPrintBed *bed);
    void calibrating();

private:
    //called by friend classes
    void emitUpdate();

    qreal _currentTemp = 0;
    qreal _targetTemp = 0;
    qreal _power = 0;
    qreal _watts = 0;
    qreal _inlineResistor = 0;
    qreal _maxPower = 0;
    qreal _maxTemp= 0;
    qreal _minTemp = 0;
    qreal _pidKD = 0;
    qreal _pidKI = 0;
    qreal _pidKP = 0;
    qreal _pullupResistor = 0;
    qreal _pwmCycleTime = 0;
    qreal _smoothTime = 0;

    QDateTime _startTime;

    Mesh _bedMesh;

    QMap<QString, AdjustmentScrew*> _adjustmentScrews;
    bool                            _adjustmentScrewsError = false;
    bool                            _hasAdjustmentScrewResult = false;
    qreal                           _adjustmentScrewsMaxDeviation = 0;

    bool                            _tiltAdjustError = false;

    Printer                        *_printer = nullptr;

    QString                         _control;
    QString                         _heaterPin;
    QString                         _sensorPin;
    QString                         _sensorType;

    Type                            _type = NonHeated;
};

#endif // BED_H
