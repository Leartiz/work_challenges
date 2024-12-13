INCLUDEPATH += \
    $$PWD/../dependency \
    $$PWD/../dependency/clickhouse \
    $$PWD/../dependency/abseil \
    $$PWD/../dependency/zstd/lib \
    $$PWD/../dependency/lz4/lib \
    $$PWD/../dependency/cityhash/src

SOURCES += \
    $$PWD/../dependency/cityhash/src/city.cc

# ------------------------------------------------------------------------

win32: {
    LUA_PATH = $$getenv(LUA_PATH)
    BOOST_PATH = $$getenv(BOOST_PATH)

    CLICKHOUSE_PATH = $$PWD/../dependency/clickhouse/build/clickhouse
    ABSL_PATH =       $$PWD/../dependency/abseil/build/absl
    ZSTD_PATH =       $$PWD/../dependency/zstd/build/VS2010/bin
    LZ4_PATH =        $$PWD/../dependency/lz4/build/VS2022/bin

    INCLUDEPATH += \
        $$BOOST_PATH \
        $$LUA_PATH\include

    LIBS += -lws2_32 -lmswsock
    LIBS += -L"$$LUA_PATH" -llua54
    LIBS += -L"$$BOOST_PATH/stage/lib"

    CONFIG(debug, debug|release) {
        message("Building in Debug mode")

        LIBS += -L"$$CLICKHOUSE_PATH/Debug"
        LIBS += -lclickhouse-cpp-lib

        LIBS += -L"$$ABSL_PATH/numeric/Debug"
        LIBS += -labsl_int128

        LIBS += -L"$$ABSL_PATH/hash/Debug"
        LIBS += -labsl_city -labsl_hash -labsl_low_level_hash

        LIBS += -L"$$LZ4_PATH/x64_Debug"
        LIBS += -lliblz4

        LIBS += -L"$$ZSTD_PATH/x64_Debug"
        LIBS += -llibzstd
    } else {
        message("Building in Release mode")

        LIBS += -L"$$CLICKHOUSE_PATH/Release"
        LIBS += -lclickhouse-cpp-lib

        LIBS += -L"$$ABSL_PATH/numeric/Release"
        LIBS += -labsl_int128

        LIBS += -L"$$ABSL_PATH/hash/Release"
        LIBS += -labsl_city -labsl_hash -labsl_low_level_hash

        LIBS += -L"$$LZ4_PATH/x64_Release"
        LIBS += -lliblz4

        LIBS += -L"$$ZSTD_PATH/x64_Release"
        LIBS += -llibzstd
    }

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

