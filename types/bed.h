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
                CounterClockwise,
                NotSet = -1
            };

            //Ratio string
            QString amount;
            QString sign;

            Direction direction = NotSet;

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

    Type type() const;

    qreal maxWatts() const;
    void setMaxWatts(qreal maxWatts);

signals:
    void meshUpdated();
    void adjustmentScrewsUpdated();
    void updated(Q3DPrintBed *bed);
    void adjustmentScrewsCalibrating();
    void adjustmentScrewsCalibrated();
    void bedMeshCalibrating();
    void bedMeshCalibrated();


protected slots:
    //called by friend classes
    void update();

protected:
    void updateAdjustmentScrews(const QMap<QString, AdjustmentScrew *> &adjustmentScrews);
    void updateBedMesh(const Mesh mesh);

private:

    qreal m_currentTemp = 0;
    qreal m_targetTemp = 0;
    qreal m_power = 0;
    qreal m_watts = 0;
    qreal m_maxWatts = 0;
    qreal m_inlineResistor = 0;
    qreal m_maxPower = 0;
    qreal m_maxTemp= 0;
    qreal m_minTemp = 0;
    qreal m_pidKD = 0;
    qreal m_pidKI = 0;
    qreal m_pidKP = 0;
    qreal m_pullupResistor = 0;
    qreal m_pwmCycleTime = 0;
    qreal m_smoothTime = 0;

    QDateTime m_startTime;

    Mesh m_bedMesh;

    QMap<QString, AdjustmentScrew*> m_adjustmentScrews;
    bool                            m_adjustmentScrewsError = false;
    bool                            m_hasAdjustmentScrewResult = false;
    bool                            m_hasBedMeshResult = false;
    bool                            m_adjustmentScrewsCalibrating = false;
    bool                            m_bedMeshCalibrating = false;
    qreal                           m_adjustmentScrewsMaxDeviation = 0;

    bool                            m_tiltAdjustError = false;

    Printer                        *m_printer = nullptr;

    QString                         m_control;
    QString                         m_heaterPin;
    QString                         m_sensorPin;
    QString                         m_sensorType;

    Type                            m_type = NonHeated;
};

#endif // BED_H
