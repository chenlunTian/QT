#-------------------------------------------------
#
# Project created by QtCreator 2018-09-27T13:35:50
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += network
CONFIG   += C++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SerialPort
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui
