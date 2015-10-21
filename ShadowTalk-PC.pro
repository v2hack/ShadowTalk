TEMPLATE = app

QT += qml quick widgets core network xml multimedia

CONFIG += c++11
CONFIG += console

RESOURCES += qml.qrc
RC_FILE += ShadowTalk.rc

# This
#QMAKE_CXXFLAGS += /MD
#QMAKE_CXXFLAGS += -fexceptions

SHADOWTALK_DEBUG_ENABLE=YES
QMAKE_LFLAGS += /NODEFAULTLIB:libcmtd.lib

INCLUDEPATH += include
INCLUDEPATH += src/core
INCLUDEPATH += src/net
INCLUDEPATH += src/widget
INCLUDEPATH += include/boost
INCLUDEPATH += include/maidsafe

# Default rules for deployment.
include(deployment.pri)


HEADERS += \
    include/im.h \
    include/qrencode.h \
    include/maidsafe/common/asio_service.h \
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
    src/widget/st_chat.h \
    src/core/st_base64.h \
    src/core/st_voice.h \
    src/core/st_picture.h \
    src/core/st_qrcode.h \
    src/core/st_thread.h \
    src/core/st_search.h
	
SOURCES += \
    src/main.cpp \
    src/core/st_cache.cpp \
    src/core/st_log.cpp \
    src/core/st_parsexml.cpp \
    src/core/st_pixelsize.cpp \
    src/core/st_utils.cpp \
    src/core/st_zebra.cpp \
    src/core/st_context.cpp \
    src/net/st_net.cpp \
    src/widget/st_friend.cpp \
    src/widget/st_group.cpp \
    src/widget/st_login.cpp \
    src/widget/st_message.cpp \
    src/widget/st_trayicon.cpp \
    src/widget/st_chat.cpp \
    src/core/st_base64.cpp \
    src/core/st_voice.cpp \
    src/core/st_picture.cpp \
    src/core/st_qrcode.cpp \
    src/core/st_context.cpp \
    src/core/st_thread.cpp \
    src/core/st_search.cpp
   
win32 {
    contains(SHADOWTALK_DEBUG_ENABLE, YES) {
        LIBS += -L$$PWD/lib/x32/debug/boost/     -llibboost_chrono-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -llibboost_date_time-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -llibboost_filesystem-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -llibboost_program_options-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -llibboost_regex-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -llibboost_system-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -llibboost_thread-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lcryptopp
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lmaidsafe_common
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lmaidsafe_passport
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_channel
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_imapi
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_nat
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_network
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_visit
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_oudp
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lproto_compiler
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lprotobuf_lite
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lprotobuf
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -ltorrent-rasterbar
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -ludt
        LIBS += -L$$PWD/lib/x32/debug/ice/       -llibpj
        LIBS += -L$$PWD/lib/x32/debug/ice/       -llibpjlib-util
        LIBS += -L$$PWD/lib/x32/debug/ice/       -llibpjnath
        LIBS += -L$$PWD/lib/x32/debug/qrcode/    -llibqrcode
    } else {
        LIBS += -L$$PWD/lib/x32/release/boost/     -llibboost_chrono-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -llibboost_date_time-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -llibboost_filesystem-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -llibboost_program_options-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -llibboost_regex-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -llibboost_system-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -llibboost_thread-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lcryptopp-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lmaidsafe_common-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lmaidsafe_passport-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_channel-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_imapi-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_oudp-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_nat-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_network-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_visit-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lproto_compiler-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lprotobuf_lite-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lprotobuf-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -ltorrent-rasterbar
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -ludt-msr
        LIBS += -L$$PWD/lib/x32/release/ice/       -llibpj
        LIBS += -L$$PWD/lib/x32/release/ice/       -llibpjlib-util
        LIBS += -L$$PWD/lib/x32/release/ice/       -llibpjnath
        LIBS += -L$$PWD/lib/x32/release/qrcode/    -llibqrcode
    }
} else {
    macx {

    } else {

    }
}


