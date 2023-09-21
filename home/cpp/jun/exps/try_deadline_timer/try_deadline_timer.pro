TEMPLATE = app

QT += core

CONFIG += console c++17
CONFIG -= app_bundle

INCLUDEPATH += ../../../../libs/boost_1_82_0
LIBS += -lws2_32

SOURCES += \
        main.cpp
