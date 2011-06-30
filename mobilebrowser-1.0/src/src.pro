TARGET = helium-mobile-browser

TEMPLATE = app

#CONFIG += meegobuild

meegobuild {
    #ugly hack, it seems there is no macro for meego builds
    #just hardcoding one here until a proper one will be provided by the SDK
    message(hackish: defining Q_OS_MEEGO !!)
    DEFINES += Q_OS_MEEGO
}

QT += declarative \
    gui \
    core \
    network \
    webkit \
    opengl \
    sql

include(utility/utility.pri)
include(models/models.pri)

SOURCES += \
    main.cpp \
    Settings.cpp \
    MainView.cpp \
    Core.cpp \
    WebViewInterface.cpp \
    CoreDbHelper.cpp \
    Logbook.cpp \
    FaviconImageProvider.cpp \
    OrientationFollower.cpp \
    Metrics.cpp


HEADERS += \
    buildconfig.h \
    Settings.h \
    MainView.h \
    LinkItem.h \
    Core.h \
    WebViewInterface.h \
    CoreDbHelper.h \
    Logbook.h \
    LogbookLinkItems.h \
    FaviconImageProvider.h \
    OrientationFollower.h \
    Metrics.h

# Used to see the QML files in the Project view of "Qt Creator"
OTHER_FILES += qmls/BrowserView.qml \
    qmls/common/VHScrollDropShadow.qml \
    qmls/common/VScrollDropShadow.qml \
    qmls/common/HScrollDropShadow.qml \
    qmls/common/ScrollBar.qml \
    qmls/BrowserViewComponents/FlickableWebView.qml \
    qmls/BrowserViewComponents/Header.qml \
    qmls/BrowserViewComponents/fieldtext/FieldText.qml \
    qmls/BrowserViewComponents/Footer.qml \
    qmls/BrowserViewComponents/FieldText.qml \
    qmls/LogbookView.qml \
    qmls/LogbookViewComponents/BookmarksListView.qml \
    qmls/LogbookViewComponents/HistoryListView.qml \
    qmls/LogbookViewComponents/MostVisitedListView.qml \
    qmls/LogbookViewComponents/TabButton.qml \
    qmls/LogbookViewComponents/TabBar.qml \
    qmls/common/EmbossedButton.qml \
    qmls/LogbookViewComponents/Header.qml \
    qmls/common/BottomDropShadow.qml \
    qmls/common/TopDropShadow.qml \
    qmls/common/Background.qml \
    qmls/common/BarIcon.qml \
    qmls/common/ToolTip.qml \
    qmls/common/FeedToolTip.qml \
    qmls/common/TemporaryMessageWithIcon.qml \
    qmls/LogbookViewComponents/LogbookListView.qml

# Resources - DON'T forget to include the QML files
RESOURCES += qmls.qrc

# Desktop Specific
#!maemo5 && !symbian {
#   linux || win32 || macosx {
#      OBJECTS_DIR = temp
#      MOC_DIR = temp
#      UI_DIR = temp
#   }
#}


Debug {
    message(Building in DEBUG mode)
    DEFINES += QT_FATAL_WARNINGS
    DEFINES += ENABLE_LOG
    #DEFINES += ENABLE_VERBOSE
    #DEFINES += INSTALL_MESSAGE_HANDLER
}

Release {
    message(Building in RELEASE mode)
}

symbian {
    include(symbian/symbian.pri)
}

maemo5 {
    include(maemo5/maemo5.pri)
}

symbian|maemo5|meegobuild {
    message(building with MOBILE_BUILD on)
    DEFINES += MOBILE_BUILD

    CONFIG += mobility
    MOBILITY += sensors
}

win32|unix {
    !meegobuild:!maemo5:!symbian {
        message(building with DESKTOP_BUILD on)
        DEFINES += DESKTOP_BUILD
    }
}

unix:!symbian {
    meego5 {
        target.path = /opt/usr/bin
    } else {
        target.path = /usr/local/bin
    }
    INSTALLS += target
}
