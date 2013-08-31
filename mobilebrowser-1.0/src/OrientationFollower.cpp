#include "OrientationFollower.h"
#include <QApplication>
#include <QInputContext>

OrientationFollower::OrientationFollower(QObject *parent) :
    QObject(parent), m_state("Landscape")
{

    // We do not follow orientation on Maemo5 as platform does the orientation change
#if !defined(Q_WS_MAEMO_5)
#ifdef ORIENTATION_ENABLE
    m_sensor = new QtMobility::QOrientationSensor(this);
    connect(m_sensor, SIGNAL(readingChanged()), SLOT(onReadingChanged()));
    m_sensor->start();
#endif
#endif
}

OrientationFollower::~OrientationFollower() {
#ifdef ORIENTATION_ENABLE
    delete m_sensor;
#endif
}

void OrientationFollower::update() {
    onReadingChanged();
}


namespace M {
enum OrientationAngle { Angle0=0, Angle90=90, Angle180=180, Angle270=270 };
}



void OrientationFollower::onReadingChanged()
{
    M::OrientationAngle mtfOrient = M::Angle0;
#ifdef ORIENTATION_ENABLE
    QtMobility::QOrientationReading* reading = m_sensor->reading();

    switch(reading->orientation())
    {
    case QtMobility::QOrientationReading::TopUp:
        m_state = "Portrait";
        mtfOrient=M::Angle270;

        emit orientationChanged();
        break;
    case QtMobility::QOrientationReading::TopDown:
        m_state = "PortaitInverted";
        mtfOrient=M::Angle90;

        emit orientationChanged();
        break;
    case QtMobility::QOrientationReading::LeftUp:
        m_state = "LandscapeInverted";
        emit orientationChanged();
        mtfOrient=M::Angle180;

        break;
    case QtMobility::QOrientationReading::RightUp:
        m_state = "Landscape";
        emit orientationChanged();
        mtfOrient=M::Angle0;

    default:
        break;
    }
#endif
    // We then update to VKB what is the current orientation
    QInputContext* context = qApp->inputContext();
    QMetaObject::invokeMethod(context,
                              "notifyOrientationChanged",
                              Q_ARG(M::OrientationAngle, mtfOrient));

}
