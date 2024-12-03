TEMPLATE = app

CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

include(../pri_files/common_deps.pri)

# ------------------------------------------------------------------------

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
