#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T16:02:46
#
#-------------------------------------------------

QMAKE_CXX = clang++
QMAKE_CC = clang

QT       += core gui
QT       += network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = remote-app-on-raspberry
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    picture.cpp \

HEADERS  += mainwindow.h \
    picture.h \

FORMS    += mainwindow.ui

RESOURCES +=
