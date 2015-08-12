TEMPLATE = app

QT += qml quick widgets core network xml

CONFIG += c++11
QMAKE_CXXFLAGS += -fno-exceptions

INCLUDEPATH += include
INCLUDEPATH += src/core
INCLUDEPATH += src/net
INCLUDEPATH += src/widget

HEADERS += \
    im.h \
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
    src/core/context.h \
    src/core/log.h \
    src/core/parsexml.h

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
    src/core/dbase.cpp \
    src/core/utils.cpp \
    src/core/log.cpp \
    src/core/parsexml.cpp


win32 {
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_chrono-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_chrono-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_chrono-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_date_time-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_date_time-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_filesystem-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_filesystem-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_program_options-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_program_options-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_regex-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_regex-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_system-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_system-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_thread-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x64/boost/ -llibboost_thread-vc120-mt-gd-1_57

    LIBS += -L$$PWD/lib/x64/peersafe/ -lcryptopp-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lmaidsafe_common-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lmaidsafe_network_viewer-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lmaidsafe_passport-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lpeersafe_channel-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lpeersafe_imapi-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lpeersafe_network-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lpeersafe_oudp-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lpeersafe_visit-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lproto_compiler-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lprotobuf_lite-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -lprotobuf-msr
    LIBS += -L$$PWD/lib/x64/peersafe/ -ltorrent-rasterbar
} else {
    macx {

    } else {

    }
}

		
RESOURCES += qml.qrc

RC_FILE += ShadowTalk.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=


INCLUDEPATH += $$PWD/lib/x64/boost
DEPENDPATH += $$PWD/lib/x64/boost
