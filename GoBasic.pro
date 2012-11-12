#-------------------------------------------------
#
# Project created by QtCreator 2012-06-19T19:17:02
#
#-------------------------------------------------

QT       += core gui

TARGET = GoBasic
TEMPLATE = app


SOURCES += main.cpp\
        gomain.cpp \
    boardmatrix.cpp \
    gameboardwidget.cpp \
    gamelogic.cpp \
    abstractplayer.cpp \
    humanplayer.cpp

HEADERS  += gomain.h \
    boardmatrix.h \
    gameboardwidget.h \
    gamelogic.h \
    abstractplayer.h \
    humanplayer.h

FORMS    += gomain.ui \
    gameboardwidget.ui

OTHER_FILES += \
    README.md

