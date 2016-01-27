#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T21:29:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrettyGoofyPrivacy
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Binary.cpp \
    Profile.cpp

HEADERS  += mainwindow.h \
    Binary.h \
    Profile.h

FORMS    += mainwindow.ui

win32:RC_ICONS += icon.ico
