#-------------------------------------------------
#
# Project created by QtCreator 2014-03-08T01:16:21
#
#-------------------------------------------------

QT       += core gui quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = beamerdmx
TEMPLATE = app

CONFIG += c++11

DEFINES += "BEAMERDMX_NAME=\\\"BeamerDMX\\\""
DEFINES += "BEAMERDMX_VERSION=\\\"0.0.1\\\""

SOURCES += src/main.cpp \
    src/lasersurface.cpp \
    src/colors.cpp \
    src/lasercontroller.cpp \
    src/painters/laserpainter.cpp \
    src/beamerwindow.cpp \
    src/painters/blackoutpainter.cpp \
    src/paintermanager.cpp \
    src/painters/standingwave.cpp

HEADERS  += \
    src/lasersurface.h \
    src/channels.h \
    src/colors.h \
    src/lasercontroller.h \
    src/painters/laserpainter.h \
    src/beamerwindow.h \
    src/painters/blackoutpainter.h \
    src/paintermanager.h \
    src/painters/standingwave.h

FORMS    +=

OTHER_FILES += \
    qml/mainwindow.qml \
    qml/beamerwindow.qml \
    qml/Fader.qml

RESOURCES += \
    beamerdmx.qrc

debug {
    DEFINES += "DEBUG"
}
