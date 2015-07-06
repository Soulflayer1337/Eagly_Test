#-------------------------------------------------
#
# Project created by QtCreator 2015-07-05T13:24:09
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Example
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    dialog/dialog.cpp \
    protocol/protocol.cpp \
    switcher/switcher.cpp

HEADERS += \
    dialog/dialog.h \
    interfaces/icall.h \
    interfaces/isendaudio.h \
    interfaces/isendpicture.h \
    interfaces/isendtext.h \
    interfaces/ivideocall.h \
    protocol/protocol.h \
    switcher/switcher.h

CONFIG += c++11
