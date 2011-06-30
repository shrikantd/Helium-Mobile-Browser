#ifndef ORIENTATIONFOLLOWER_H
#define ORIENTATIONFOLLOWER_H

#include <QObject>
#include <QString>

#ifdef Q_OS_MEEGO
    class QtMobility::QOrientationSensor;
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
#ifdef Q_OS_MEEGO
    QtMobility::QOrientationSensor* m_sensor;
#endif
};

#endif // ORIENTATIONFOLLOWER_H
