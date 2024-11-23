QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LUA_PATH = $$getenv(LUA_PATH)

INCLUDEPATH += \
    $$LUA_PATH\include
LIBS += -L"$$LUA_PATH" -llua54

INCLUDEPATH += \
    $$PWD\..\app \
    $$PWD/../dependency

SOURCES += \
    tst_common.cpp \
    $$PWD/../app/service/impl/lua_math.cpp

HEADERS += \
    tst_common.h
