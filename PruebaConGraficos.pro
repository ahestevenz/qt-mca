#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T11:09:17
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PruebaConGraficos
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    apComunicacionMCA.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    apComunicacionMCA.hpp

LIBS += -lboost_system

FORMS    += mainwindow.ui
