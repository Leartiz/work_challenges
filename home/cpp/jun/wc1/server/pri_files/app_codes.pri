message("`app_sources.pri` has PWD: $$PWD")

HEADERS += \
    $$PWD/../app/adapters/interfaces/tcp/client_connection.h \
    $$PWD/../app/adapters/interfaces/tcp/client_context.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/auth/auth_req_payload.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/math/req_payload_with_expr.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/math/res_result_with_double.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/request_payload.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/response_result.h \
    $$PWD/../app/adapters/interfaces/tcp/listener.h \
    $$PWD/../app/adapters/interfaces/tcp/message_creator.h \
    $$PWD/../app/adapters/interfaces/tcp/request_context.h \
    $$PWD/../app/adapters/interfaces/tcp/request_handler.h \
    $$PWD/../app/adapters/interfaces/tcp/tcp_common.h \
    $$PWD/../app/config/server_config.h \
    $$PWD/../app/logging/impl/boost/main_boost_logger.h \
    $$PWD/../app/service/impl/lua_math.h \
    $$PWD/../app/service/math_service.h \
    $$PWD/../app/logging/logging.h \
    $$PWD/../app/service/services.h \
    $$PWD/../app/adapters/infrastructure/storage/log/impl/clickhouse/clickhouse_storage.h \
    $$PWD/../app/adapters/infrastructure/storage/log/log_storage.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/request.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/common_validator.h \
    $$PWD/../app/adapters/interfaces/tcp/message_parser.h \
    $$PWD/../app/utils/error/error_utils.h \
    $$PWD/../app/utils/uuid/uuid_utils.h \
    $$PWD/../app/adapters/interfaces/tcp/dto/response.h

SOURCES += \
    $$PWD/../app/adapters/interfaces/tcp/client_context.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/auth/auth_req_payload.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/math/req_payload_with_expr.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/math/res_result_with_double.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/response_result.cpp \
    $$PWD/../app/adapters/interfaces/tcp/message_creator.cpp \
    $$PWD/../app/adapters/interfaces/tcp/request_context.cpp \
    $$PWD/../app/adapters/interfaces/tcp/request_handler.cpp \
    $$PWD/../app/adapters/interfaces/tcp/tcp_common.cpp \
    $$PWD/../app/config/server_config.cpp \
    $$PWD/../app/logging/impl/boost/main_boost_logger.cpp \
    $$PWD/../app/logging/logging.cpp \
    $$PWD/../app/adapters/interfaces/tcp/client_connection.cpp \
    $$PWD/../app/adapters/interfaces/tcp/listener.cpp \
    $$PWD/../app/service/impl/lua_math.cpp \
    $$PWD/../app/adapters/infrastructure/storage/log/impl/clickhouse/clickhouse_storage.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/common_validator.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/request.cpp \
    $$PWD/../app/adapters/interfaces/tcp/message_parser.cpp \
    $$PWD/../app/utils/error/error_utils.cpp \
    $$PWD/../app/utils/uuid/uuid_utils.cpp \
    $$PWD/../app/adapters/interfaces/tcp/dto/response.cpp
