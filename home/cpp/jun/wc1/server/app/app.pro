TEMPLATE = app

CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

# ------------------------------------------------------------------------

include(../pri_files/common_deps.pri)
include(../pri_files/app_sources.pri)

# ------------------------------------------------------------------------

SOURCES += \
    adapters/interfaces/tcp/dto/auth/auth_payload.cpp \
    adapters/interfaces/tcp/message_parser.cpp \
    adapters/interfaces/tcp/request_handler.cpp \
    main.cpp

HEADERS += \
    $$PWD/../config/config.h \
    $$PWD/../app/adapters/interfaces/tcp/client_connection.h \
    $$PWD/../app/adapters/interfaces/tcp/listener.h \
    $$PWD/../app/service/impl/lua_math.h \
    $$PWD/../app/service/math_service.h \
    $$PWD/../app/logging/impl/boost/boost_logger.h \
    $$PWD/../app/logging/logging.h \
    $$PWD/../app/adapters/infrastructure/storage/log/impl/clickhouse/clickhouse_storage.h \
    $$PWD/../app/adapters/infrastructure/storage/log/log_storage.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/math/payload_with_expr.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/payload.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/request.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/common_validator.h \
    adapters/interfaces/tcp/dto/auth/auth_payload.h \
    adapters/interfaces/tcp/message_parser.h \
    adapters/interfaces/tcp/request_handler.h

OTHER_FILES += \
    $$PWD/../.env

# ------------------------------------------------------------------------

message("Pwd: $$PWD")
message("Assembly Catalog: $$OUT_PWD")

QMAKE_PRE_LINK += $$quote(echo qmake_pre_link)
win32: {
    message("Copying a file: .env to folder: $$OUT_PWD")

    QMAKE_PRE_LINK += echo Starting file copy...
    QMAKE_PRE_LINK += robocopy $$quote($$PWD/..) $$quote($$OUT_PWD) .env
}

# ------------------------------------------------------------------------
