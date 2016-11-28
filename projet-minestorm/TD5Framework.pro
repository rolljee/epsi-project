QMAKE_CXX = clang++
QMAKE_CC = clang

QT       += core gui

CONFIG+=C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minestorm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    gameboard.cpp \
    game.cpp \
    minestorm.cpp \
    bullet.cpp \
    ship.cpp \
    box.cpp \
    mine.cpp \
    explosion.cpp \
    threadbullet.cpp

HEADERS  += mainwindow.h \
    controller.h \
    gameboard.h \
    game.h \
    minestorm.h \
    bullet.h \
    ship.h \
    box.h \
    mine.h \
    explosion.h \
    threadbullet.h

FORMS    +=

RESOURCES += \
    ressources.qrc
