TEMPLATE = app

QT += qml quick widgets core network xml multimedia

CONFIG += c++11
CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= gui




# This
#QMAKE_CXXFLAGS += /MD

# Or that

QMAKE_LFLAGS += /NODEFAULTLIB:libcmtd.lib

QMAKE_CXXFLAGS += -fexceptions
INCLUDEPATH += include
INCLUDEPATH += src/core
INCLUDEPATH += src/net
INCLUDEPATH += src/widget

HEADERS += \
    include/im.h \
    src/core/st_cache.h \
    src/core/st_pixelsize.h \
    src/core/st_parsexml.h \
    src/core/st_log.h \
    src/core/st_context.h \
    src/core/st_utils.h \
    src/core/st_zebra.h \
    src/net/st_net.h \
    src/widget/st_friend.h \
    src/widget/st_message.h \
    src/widget/st_login.h \
    src/widget/st_group.h \
    src/widget/st_trayicon.h \
    src/core/st_base64.h \
    src/core/st_voice.h
	
SOURCES += \
    src/main.cpp \
    src/core/st_cache.cpp \
    src/core/st_log.cpp \
    src/core/st_parsexml.cpp \
    src/core/st_pixelsize.cpp \
    src/core/st_utils.cpp \
    src/core/st_zebra.cpp \
    src/net/st_net.cpp \
    src/widget/st_friend.cpp \
    src/widget/st_group.cpp \
    src/widget/st_login.cpp \
    src/widget/st_message.cpp \
    src/widget/st_trayicon.cpp \
    src/core/st_base64.cpp \
    src/core/st_voice.cpp
   
win32 {
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_chrono-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_chrono-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_chrono-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_date_time-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_date_time-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_filesystem-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_filesystem-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_program_options-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_program_options-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_regex-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_regex-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_system-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_system-vc120-mt-gd-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_thread-vc120-mt-1_57
    LIBS += -L$$PWD/lib/x32/boost/ -llibboost_thread-vc120-mt-gd-1_57

    LIBS += -L$$PWD/lib/x32/peersafe/ -lcryptopp-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lmaidsafe_common-msr
#    LIBS += -L$$PWD/lib/x32/peersafe/ -lmaidsafe_network_viewer-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lmaidsafe_passport-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lpeersafe_channel-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lpeersafe_imapi-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lpeersafe_network-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lpeersafe_oudp-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lpeersafe_visit-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lproto_compiler-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lprotobuf_lite-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -lprotobuf-msr
    LIBS += -L$$PWD/lib/x32/peersafe/ -ltorrent-rasterbar

    LIBS += -L$$PWD/lib/x32/ice/ -llibpj
    LIBS += -L$$PWD/lib/x32/ice/ -llibpjlib-util
    LIBS += -L$$PWD/lib/x32/ice/ -llibpjnath
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
