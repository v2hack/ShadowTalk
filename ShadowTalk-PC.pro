TEMPLATE = app

QT += qml quick widgets core

CONFIG += c++11
QMAKE_CXXFLAGS += -fno-exceptions

INCLUDEPATH += include
INCLUDEPATH += src/core
INCLUDEPATH += src/net
INCLUDEPATH += src/widget

HEADERS += \
    src/net/net.h \
    src/widget/friend_list_layout.h \
    src/widget/login.h \
    src/core/pixelsize.h \
    src/widget/friend.h \
    src/core/cache.h \
    src/widget/group.h \
    src/widget/message.h \
    src/widget/trayicon.h \
    src/core/dbase.h \
    src/core/utils.h \
    src/core/context.h

SOURCES += \
    src/main.cpp \
    src/net/net.cpp \
    src/widget/login.cpp \
    src/core/pixelsize.cpp \
    src/core/cache.cpp \
    src/widget/group.cpp \
    src/widget/friend.cpp \
    src/widget/message.cpp \
    src/widget/trayicon.cpp \
    src/core/dbase.cpp

		
RESOURCES += qml.qrc


RC_FILE += ShadowTalk.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=
