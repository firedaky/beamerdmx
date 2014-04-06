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
    src/lasersurface.cpp

HEADERS  += \
    src/lasersurface.h

FORMS    +=

OTHER_FILES += \
    qml/mainwindow.qml \
    qml/beamerwindow.qml

RESOURCES += \
    beamerdmx.qrc

debug {
    DEFINES += "DEBUG"
}
