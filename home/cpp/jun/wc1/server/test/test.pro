TEMPLATE = app

QT += testlib
QT -= gui

CONFIG += c++17
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

include(../pri_files/common_deps.pri)

# ------------------------------------------------------------------------

INCLUDEPATH += \
    $$PWD\..\app 

SOURCES += \
    tst_common.cpp \
    $$PWD/../app/service/impl/lua_math.cpp

HEADERS += \
    tst_common.h
