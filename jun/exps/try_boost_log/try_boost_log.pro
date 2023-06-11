TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../../libs/boost_1_82_0
LIBS += -L"../../../../libs/boost_1_82_0/stage/lib" \
    -llibboost_log-vc143-mt-gd-x32-1_82 \
    -llibboost_log-vc143-mt-gd-x64-1_82 \
    -llibboost_log-vc143-mt-x32-1_82 \
    -llibboost_log-vc143-mt-x64-1_82

SOURCES += \
        main.cpp
