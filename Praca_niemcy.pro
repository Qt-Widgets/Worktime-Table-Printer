#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T18:21:30
#
#-------------------------------------------------

QT       += core gui printsupport
CONFIG += static

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Praca_niemcy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    czas.cpp \
    przeliczwalute.cpp \
    startdialog.cpp

HEADERS  += mainwindow.h \
    czas.h \
    przeliczwalute.h \
    startdialog.h

FORMS    += mainwindow.ui \
    przeliczwalute.ui \
    startdialog.ui

CONFIG+= static
