QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/db/dbfacade.cpp \
    src/db/entities/simpleentity.cpp \
    src/db/sqlqueryconverter.cpp \
    src/db/strategy_conct/strategyconct.cpp \
    src/db/strategy_conct/strategyconctmysql.cpp \
    src/db/strategy_conct/strategyconctsqlite.cpp \
    src/main.cpp \
    src/model/treeitem.cpp \
    src/view/conctwidget.cpp \
    src/view/mainwindow.cpp \
    src/model/treemodel.cpp

INCLUDEPATH += include
HEADERS += \
    include/db/dbfacade.h \
    include/db/entities/simpleentity.h \
    include/db/sqlqueryconverter.h \
    include/db/strategy_conct/strategyconct.h \
    include/db/strategy_conct/strategyconctmysql.h \
    include/db/strategy_conct/strategyconctsqlite.h \
    include/model/treeitem.h \
    include/model/treemodel.h \
    include/view/conctwidget.h \
    include/view/mainwindow.h

FORMS += \
    ui/conctwidget.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rec.qrc
