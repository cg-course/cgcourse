#-------------------------------------------------
#
# Project created by QtCreator 2016-02-27T15:11:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gridshaders
TEMPLATE = app


SOURCES += main.cpp \
    openglwidget.cpp

HEADERS  += \
    openglwidget.h

FORMS    +=

DISTFILES += \
    shader_basic.frag \
    shader_basic.vert

RESOURCES += \
    res.qrc
