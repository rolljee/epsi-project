#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T16:31:51
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT       += network
QT += concurrent
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Arduino-TCP-Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mytcpserver.cpp \
    socket.cpp \
    sqlconnexion.cpp

HEADERS  += mainwindow.h \
    mytcpserver.h \
    socket.h \
    sqlconnexion.h

FORMS    += mainwindow.ui
