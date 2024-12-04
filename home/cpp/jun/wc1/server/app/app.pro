TEMPLATE = app

CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

include(../pri_files/common_deps.pri)

# ------------------------------------------------------------------------

SOURCES += \
        $$PWD/../app/config/config.cpp \
        $$PWD/../app/logging/impl/boost/boost_logger.cpp \
        $$PWD/../app/logging/logging.cpp \
        $$PWD/../app/adapters/interfaces/tcp/client_connection.cpp \
        $$PWD/../app/adapters/interfaces/tcp/listener.cpp \
        $$PWD/../app/service/impl/lua_math.cpp \
        main.cpp

HEADERS += \
    $$PWD/../config/config.h \
    $$PWD/../app/adapters/interfaces/tcp/client_connection.h \
    $$PWD/../app/adapters/interfaces/tcp/listener.h \
    $$PWD/../app/service/impl/lua_math.h \
    $$PWD/../app/service/service.h \
    $$PWD/../logging/impl/boost/boost_logger.h \
    $$PWD/../logging/logging.h

OTHER_FILES += \
    $$PWD/../.env
