TEMPLATE = app

# ------------------------------------------------------------------------

CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

# ------------------------------------------------------------------------

include(../pri_files/common_deps.pri)
include(../pri_files/app_sources.pri)

# ------------------------------------------------------------------------

SOURCES += \
    main.cpp

INCLUDEPATH += \
    $$PWD/../app

HEADERS += \
    adapters/interfaces/tcp/client_connection.h \
    adapters/interfaces/tcp/listener.h \
    config/server_config.h \
    service/impl/lua_math.h \
    service/math_service.h \
    logging/impl/boost/boost_logger.h \
    logging/logging.h \
    adapters/infrastructure/storage/log/impl/clickhouse/clickhouse_storage.h \
    adapters/infrastructure/storage/log/log_storage.h \
    adapters/interfaces/tcp/dto/math/payload_with_expr.h \
    adapters/interfaces/tcp/dto/payload.h \
    adapters/interfaces/tcp/dto/request.h \
    adapters/interfaces/tcp/dto/common_validator.h \
    adapters/interfaces/tcp/dto/auth/auth_payload.h \
    adapters/interfaces/tcp/message_parser.h \
    adapters/interfaces/tcp/request_handler.h \
    utils/error/error_utils.h

OTHER_FILES += \
    $$PWD/../.env

# ------------------------------------------------------------------------

# doesn't work?

message("Pwd: $$PWD")
message("Assembly Catalog: $$OUT_PWD")

QMAKE_PRE_LINK += $$quote(echo qmake_pre_link)
win32: {
    message("Copying a file: .env to folder: $$OUT_PWD")

    QMAKE_PRE_LINK += echo Starting file copy...
    QMAKE_PRE_LINK += robocopy $$quote($$PWD/..) $$quote($$OUT_PWD) .env
}

# ------------------------------------------------------------------------
