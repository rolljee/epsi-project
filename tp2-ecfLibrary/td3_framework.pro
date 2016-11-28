#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T10:34:12
#
#-------------------------------------------------

QMAKE_CXX = clang++
QMAKE_CC = clang

QT       += core gui
QT += concurrent
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = td3_ex1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    directoryselector.cpp \
    filepool.cpp \
    findinfile.cpp \
    zippedbuffer.cpp \
    zippedbufferpool.cpp \
    zipper.cpp \
    writer.cpp \
    epsifilecompressor.cpp \
    fileselector.cpp

HEADERS  += mainwindow.h \
    directoryselector.h \
    filepool.h \
    findinfile.h \
    zippedbuffer.h \
    zippedbufferpool.h \
    zipper.h \
    writer.h \
    epsifilecompressor.h \
    fileselector.h


FORMS    +=
