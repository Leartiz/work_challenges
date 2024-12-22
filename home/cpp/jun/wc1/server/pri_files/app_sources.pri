message("`app_sources.pri` has PWD: $$PWD")

SOURCES += \
    $$PWD/../app/config/server_config.cpp \
    $$PWD/../app/logging/impl/boost/boost_logger.cpp \
    $$PWD/../app/logging/logging.cpp \
    $$PWD/../app/adapters/interfaces/tcp/client_connection.cpp \
    $$PWD/../app/adapters/interfaces/tcp/listener.cpp \
    $$PWD/../app/service/impl/lua_math.cpp \
    $$PWD/../app/adapters/infrastructure/storage/log/impl/clickhouse/clickhouse_storage.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/math/payload_with_expr.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/common_validator.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/request.cpp \
    $$PWD/../app/adapters/interfaces/tcp/message_parser.cpp \
    $$PWD/../app/adapters/interfaces/tcp/request_handler.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/auth/auth_payload.cpp \
    $$PWD/../app/utils/error/error_utils.cpp
