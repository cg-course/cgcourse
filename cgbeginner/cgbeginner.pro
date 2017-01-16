
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cgbeginner
TEMPLATE = app


SOURCES += main.cpp \
    openglwidget.cpp

HEADERS  += \
    openglwidget.h

FORMS    +=

RESOURCES += \
    res.qrc
