QT += testlib core
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_app.cpp \
    ../app/coordconverter.cpp

INCLUDEPATH += ../app
HEADERS += \
    tst_app.h
