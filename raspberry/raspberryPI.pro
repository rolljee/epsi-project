#-------------------------------------------------
#
# Project created by QtCreator 2016-01-08T11:58:57
#
#-------------------------------------------------

QMAKE_CXX = clang++
QMAKE_CC = clang

QT += sql
QT       += core
QT       += network
QT       -= gui
QT += concurrent
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raspberryPI
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mytcpserver.cpp \
    mainwindow.cpp \
    sqlconnexion.cpp \
    worker.cpp \
    socket.cpp

HEADERS += \
    mytcpserver.h \
    mainwindow.h \
    sqlconnexion.h \
    worker.h \
    socket.h

FORMS += \
    mainwindow.ui

RESOURCES +=
