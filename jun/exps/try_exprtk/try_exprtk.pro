TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -bigobj

INCLUDEPATH += ../../../../libs/exprtk
SOURCES += \
        main.cpp
