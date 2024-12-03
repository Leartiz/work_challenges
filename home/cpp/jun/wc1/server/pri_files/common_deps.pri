INCLUDEPATH += \
    $$PWD/../dependency

win32: {
    LUA_PATH = $$getenv(LUA_PATH)
    BOOST_PATH = $$getenv(BOOST_PATH)

    INCLUDEPATH += \
        $$BOOST_PATH \
        $$LUA_PATH\include

    LIBS += -lws2_32 -lmswsock
    LIBS += -L"$$LUA_PATH" -llua54
    LIBS += -L"$$BOOST_PATH/stage/lib"

} else: unix: {
    INCLUDEPATH += \
        /usr/include/lua5.4

    LIBS += -llua5.4

    BOOST_INCLUDE_DIR=$$getenv(BOOST_INCLUDE_DIR)
    BOOST_LIBRARY_DIR=$$getenv(BOOST_LIBRARY_DIR)

    message("BOOST_INCLUDE_DIR: $$BOOST_INCLUDE_DIR")
    message("BOOST_LIBRARY_DIR: $$BOOST_LIBRARY_DIR")

    INCLUDEPATH += $$BOOST_INCLUDE_DIR

    # Why doesn't this work?
    # LIBS += -L"$$BOOST_LIBRARY_DIR"
    LIBS += \
        $$BOOST_LIBRARY_DIR/libboost_system.a \
        $$BOOST_LIBRARY_DIR/libboost_thread.a \
        $$BOOST_LIBRARY_DIR/libboost_log_setup.a \
        $$BOOST_LIBRARY_DIR/libboost_log.a \
        $$BOOST_LIBRARY_DIR/libboost_filesystem.a

    LIBS += -lpthread
    
}

