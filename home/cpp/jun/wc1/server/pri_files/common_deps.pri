# ------------------------------------------------------------------------

INCLUDEPATH += \
    $$PWD/../dependency \
    $$PWD/../dependency/clickhouse \
    $$PWD/../dependency/clickhouse/absl \
    $$PWD/../dependency/clickhouse/cityhash \
    $$PWD/../dependency/clickhouse/lz4 \
    $$PWD/../dependency/clickhouse/zstd \
    $$PWD/../dependency/laserpants \
    $$PWD/../dependency/strutil

# ------------------------------------------------------------------------

win32: {
    LUA_PATH = $$getenv(LUA_PATH)
    BOOST_PATH = $$getenv(BOOST_PATH)

# ------------------------------------------------------------------------

    CLICKHOUSE_BUILD_PATH = $$PWD/../dependency/clickhouse/build/clickhouse
    CLICKHOUSE_CONTRIB_PATH = $$CLICKHOUSE_PATH/../contrib

    ABSL_BUILD_PATH =     $$CLICKHOUSE_CONTRIB_PATH/absl/absl
    CITYHASH_BUILD_PATH = $$CLICKHOUSE_CONTRIB_PATH/cityhash/cityhash
    LZ4_BUILD_PATH =      $$CLICKHOUSE_CONTRIB_PATH/lz4/lz4
    ZSTD_BUILD_PATH =     $$CLICKHOUSE_CONTRIB_PATH/zstd/zstd

# ------------------------------------------------------------------------

    INCLUDEPATH += \
        $$BOOST_PATH \
        $$LUA_PATH\include

    LIBS += -lws2_32 -lmswsock

    LIBS += -L"$$LUA_PATH/lib" -llua51
    LIBS += -L"$$BOOST_PATH/stage/lib"

    CONFIG(debug, debug|release) {
        message("Building in Debug mode")

        LIBS += -L"$$CLICKHOUSE_PATH/Debug"
        LIBS += -lclickhouse-cpp-lib

        LIBS += -L"$$ABSL_BUILD_PATH/Debug"
        LIBS += -labsl_int128

        LIBS += -L"$$CITYHASH_BUILD_PATH/Debug"
        LIBS += -lcityhash

        LIBS += -L"$$LZ4_BUILD_PATH/Debug"
        LIBS += -llz4

        LIBS += -L"$$ZSTD_PATH/Debug"
        LIBS += -lzstdstatic
    } else {
        message("Building in Release mode")

        LIBS += -L"$$CLICKHOUSE_PATH/Release"
        LIBS += -lclickhouse-cpp-lib

        LIBS += -L"$$ABSL_BUILD_PATH/Release"
        LIBS += -labsl_int128

        LIBS += -L"$$CITYHASH_BUILD_PATH/Release"
        LIBS += -lcityhash

        LIBS += -L"$$LZ4_BUILD_PATH/Release"
        LIBS += -llz4

        LIBS += -L"$$ZSTD_PATH/Release"
        LIBS += -lzstdstatic
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

