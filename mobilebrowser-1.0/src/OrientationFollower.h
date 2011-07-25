#ifndef ORIENTATIONFOLLOWER_H
#define ORIENTATIONFOLLOWER_H

#include <QObject>
#include <QString>
#include <QDesktopWidget>

#ifdef Q_OS_MEEGO
    class QtMobility::QOrientationSensor;
#endif

class OrientationFollower : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString state READ state NOTIFY orientationChanged)
    Q_PROPERTY(int screenWidth READ screenWidth NOTIFY orientationChanged)
    Q_PROPERTY(int screenHeight READ screenHeight NOTIFY orientationChanged)
    Q_PROPERTY(int xPosition READ xPosition NOTIFY orientationChanged)
    Q_PROPERTY(int yPosition READ yPosition NOTIFY orientationChanged)

    Q_PROPERTY(int landscapeRotation READ landscapeRotation NOTIFY orientationChanged);
    Q_PROPERTY(int landscapeInvertedRotation READ landscapeInvertedRotation NOTIFY orientationChanged);
    Q_PROPERTY(int portraitRotation READ portraitRotation NOTIFY orientationChanged);
    Q_PROPERTY(int portraitInvertedRotation READ portraitInvertedRotation NOTIFY orientationChanged);

public:
    explicit OrientationFollower(QObject *parent = 0);
    ~OrientationFollower();
    inline QString state() const { return m_state; }
    void update();

    QString state();

    int screenWidth();
    int screenHeight();

    int xPosition();
    int yPosition();

    int landscapeRotation();
    int landscapeInvertedRotation();
    int portraitRotation();
    int portraitInvertedRotation();

signals:
    void orientationChanged();

private slots:
    void onReadingChanged();

    void screenResized(int screen);

private:
    QDesktopWidget  m_desktopWidget;
    QSize           m_screenSize;
    QString m_state;
#ifdef Q_OS_MEEGO
    QtMobility::QOrientationSensor* m_sensor;
#endif
};

#endif // ORIENTATIONFOLLOWER_H
