TEMPLATE = app

CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

win32: {
    LUA_PATH = $$getenv(LUA_PATH)
    BOOST_PATH = $$getenv(BOOST_PATH)

    INCLUDEPATH += \
        $$BOOST_PATH \
        $$LUA_PATH\include \
        $$PWD/../dependency

    LIBS += -lws2_32 -lmswsock
    LIBS += -L"$$LUA_PATH" -llua54
    LIBS += -L"$$BOOST_PATH/stage/lib"

} else: unix: {
    INCLUDEPATH += \
        /usr/include/lua5.4 \
        $$PWD/../dependency

    LIBS += -llua5.4

    BOOST_INCLUDE_DIR=$$getenv(BOOST_INCLUDE_DIR)
    BOOST_LIBRARY_DIR=$$getenv(BOOST_LIBRARY_DIR)

    INCLUDEPATH += \
        $$BOOST_INCLUDE_DIR

    LIBS += \
        -L$$BOOST_LIBRARY_DIR \
        -lboost_system \
        -lboost_filesystem \
        -lboost_thread \
        -lboost_date_time \
        -lboost_log_setup \
        -lboost_log
}

SOURCES += \
        main.cpp \
        $$PWD/../app/adapters/interfaces/tcp/client_connection.cpp \
        $$PWD/../app/adapters/interfaces/tcp/listener.cpp \
        $$PWD/../app/service/impl/lua_math.cpp

HEADERS += \
    $$PWD/../app/adapters/interfaces/tcp/client_connection.h \
    $$PWD/../app/adapters/interfaces/tcp/listener.h \
    $$PWD/../app/service/impl/lua_math.h \
    $$PWD/../app/service/service.h

OTHER_FILES += \
    $$PWD/../.env
