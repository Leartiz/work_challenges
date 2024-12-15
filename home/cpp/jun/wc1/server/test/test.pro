TEMPLATE = app

QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++20

# ------------------------------------------------------------------------

include(../pri_files/common_deps.pri)
include(../pri_files/app_sources.pri)

# ------------------------------------------------------------------------

INCLUDEPATH += \
    $$PWD\..\app 

SOURCES += \
    tst_common.cpp

HEADERS += \
    tst_common.h
