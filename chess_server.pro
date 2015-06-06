#-------------------------------------------------
#
# Project created by QtCreator 2015-06-06T12:58:40
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = chess_server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    chess_server.cpp \
    chess.cpp \
    player_thread.cpp

HEADERS += \
    chess_server.h \
    chess.h \
    player_thread.h
