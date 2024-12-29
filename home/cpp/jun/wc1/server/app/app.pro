TEMPLATE = app

# ------------------------------------------------------------------------

CONFIG += console c++20
CONFIG -= app_bundle
CONFIG -= qt

# ------------------------------------------------------------------------

include(../pri_files/common_deps.pri)
include(../pri_files/app_codes.pri)

# ------------------------------------------------------------------------

SOURCES += \
    main.cpp

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
