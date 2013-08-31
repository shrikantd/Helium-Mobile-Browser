#ifndef ORIENTATIONFOLLOWER_H
#define ORIENTATIONFOLLOWER_H

#include <QString>
#include <QObject>

#ifdef ORIENTATION_ENABLE
#include "qorientationsensor.h"
#endif

class OrientationFollower : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state NOTIFY orientationChanged)

public:
    explicit OrientationFollower(QObject *parent = 0);
    ~OrientationFollower();
    inline QString state() const { return m_state; }
    void update();

signals:
    void orientationChanged();

private slots:
    void onReadingChanged();

private:
    QString m_state;
#ifdef ORIENTATION_ENABLE
    QtMobility::QOrientationSensor* m_sensor;
#endif
};

#endif // ORIENTATIONFOLLOWER_H
