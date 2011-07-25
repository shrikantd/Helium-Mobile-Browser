#include "OrientationFollower.h"

#ifdef Q_OS_MEEGO
    #include "qorientationsensor.h"
#endif

#include <QApplication>
#include <QInputContext>


#define DEFAULT_WIDTH                     800
#define DEFAULT_HEIGHT                    480

#include "macros.h"


namespace M {
    enum OrientationAngle { Angle0=0, Angle90=90, Angle180=180, Angle270=270 };
}


OrientationFollower::OrientationFollower(QObject *parent) :
    QObject(parent)
{
    //screenResized(-1);

#if defined(Q_OS_MEEGO)
    m_sensor = new QtMobility::QOrientationSensor(this);
    connect(m_sensor, SIGNAL(readingChanged()), SLOT(onReadingChanged()));
    m_sensor->start();
#endif
    bool connected = connect(&m_desktopWidget, SIGNAL(resized(int)), this, SLOT(screenResized(int)) );
    QDEBUG_EXP("****************** OrientationFollower::CONNECTED", connected);
}

OrientationFollower::~OrientationFollower() {
#if defined(Q_OS_MEEGO)
    delete m_sensor;
#endif
}

void OrientationFollower::update() {
    onReadingChanged();
}

QString OrientationFollower::state() {
#ifdef Q_OS_MEEGO
    QtMobility::QOrientationReading* reading = m_sensor->reading();
    M::OrientationAngle mtfOrient = M::Angle0;

    switch(reading->orientation())
    {
    case QtMobility::QOrientationReading::TopUp:
        m_state = "Portrait";
        mtfOrient=M::Angle270;
        break;
    case QtMobility::QOrientationReading::TopDown:
        m_state = "PortaitInverted";
        mtfOrient=M::Angle90;
        break;
    case QtMobility::QOrientationReading::LeftUp:
        m_state = "LandscapeInverted";
        mtfOrient=M::Angle180;
        break;
    case QtMobility::QOrientationReading::RightUp:
        m_state = "Landscape";
        mtfOrient=M::Angle0;
    default:
        break;
    }

    // We then update to VKB what is the current orientation
    QInputContext* context = qApp->inputContext();
    QMetaObject::invokeMethod(context,
                              "notifyOrientationChanged",
                              Q_ARG(M::OrientationAngle, mtfOrient));

#else defined (Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
    m_screenSize.setWidth( screenWidth() );
    m_screenSize.setHeight( screenHeight() );
    m_state = m_screenSize.width() > m_screenSize.height() ? "Landscape" : "Portrait";
#endif
    QDEBUG_EXP("OrientationFollower::onReadingChanged()","width:" << m_screenSize.width() << "heigth:" << m_screenSize.height() << "state:" << m_state );
    return m_state;
}

int OrientationFollower::screenWidth() {
    QDEBUG_EXP("OrientationFollower::screenWidth()", m_desktopWidget.screenGeometry().width());
#if defined(DESKTOP_BUILD)
    return DEFAULT_WIDTH;
#else
    return m_desktopWidget.screenGeometry().width();
#endif
}

int OrientationFollower::screenHeight() {
    QDEBUG_EXP("OrientationFollower::screenHeight()",m_desktopWidget.screenGeometry().height());
#if defined(DESKTOP_BUILD)
    return DEFAULT_HEIGHT;
#else
    return m_desktopWidget.screenGeometry().height();
#endif
}

int OrientationFollower::xPosition() {
    int defaultPosition = 0;
    int rotatedPosition = (screenWidth() - screenHeight()) / 2;
    int xPos = 0;

#if defined(DESKTOP_BUILD) || defined(Q_OS_MEEGO) || defined(Q_WS_MAEMO_5)
    xPos = ( m_state == "Landscape" || m_state == "LandscapeInverted" ) ? defaultPosition : rotatedPosition;
#elif defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
    xPos = 0;
#endif
    QDEBUG_EXP("OrientationFollower::xPosition()","xPosition:" << xPos);
    return xPos;
}

int OrientationFollower::yPosition() {
    int defaultPosition = 0;
    int rotatedPosition = -(screenWidth() - screenHeight()) / 2;
    int yPos = 0;
#if defined(DESKTOP_BUILD) || defined(Q_OS_MEEGO)
    yPos = ( m_state == "Landscape" || m_state == "LandscapeInverted" ) ? defaultPosition : rotatedPosition;
#elif defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
    yPos = 0;
#endif
    QDEBUG_EXP("OrientationFollower::yPosition()","yPosition:" << yPos);
    return yPos;
}

int OrientationFollower::landscapeRotation() {
    int rotation = 0;
#if defined(DESKTOP_BUILD) || defined(Q_OS_MEEGO)
    rotation = 0;
#elif defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
    rotation = 0;
#endif
    QDEBUG_EXP("OrientationFollower::landscapeRotation()","landscapeRotation:" << rotation);
    return rotation;
}

int OrientationFollower::landscapeInvertedRotation() {
    return landscapeRotation() + M::Angle180;
}

int OrientationFollower::portraitRotation() {
    int correction = 0;
#if defined(DESKTOP_BUILD) || defined(Q_OS_MEEGO)
    correction + M::Angle270;
#elif defined(Q_OS_SYMBIAN) || defined(Q_WS_MAEMO_5)
    correction = 0;
#endif
    correction = landscapeRotation() + correction;
    QDEBUG_EXP("OrientationFollower::portraitRotation()","portraitRotation:" << correction);
    return correction;
}

int OrientationFollower::portraitInvertedRotation() {
    return portraitRotation() + M::Angle180;
}

void OrientationFollower::onReadingChanged()
{
    emit orientationChanged();
}

void OrientationFollower::screenResized(int screen) {
    QDEBUG_EXP("OrientationFollower::screenResized()","**********");
    if( screen == -1 ) {
        QSize screenSize;
#if defined(DESKTOP_BUILD)
        //desktop build, defaults
        screenSize.setWidth( DEFAULT_WIDTH );
        screenSize.setHeight( DEFAULT_HEIGHT );
#elif defined(MOBILE_BUILD)
        screenSize.setWidth( m_desktopWidget.screenGeometry().width() );
        screenSize.setHeight( m_desktopWidget.screenGeometry().height() );
#else
#error "not a MOBILE_BUILD nor a DESKTOP_BUILD, check your code dude!"
#endif
        m_screenSize = screenSize;
#ifndef Q_OS_MEEGO
        onReadingChanged();
#endif
    }
}
