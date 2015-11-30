TEMPLATE = app
TARGET = ShadowTalk

QT += qml quick widgets core network xml multimedia

#CONFIG += console
CONFIG += c++11
CONFIG += qtquickcompiler

RESOURCES += qml.qrc
RCC_DIR = GeneratedFiles

win32:RC_FILE += ShadowTalk.rc
macx:ICON = shadowtalk.icns
#macx:{
  #QT+= macextras
  #QMAKE_INFO_PLIST = app.plist
#}

MOC_DIR = GeneratedFiles

# This
#QMAKE_CXXFLAGS += /MD
#QMAKE_CXXFLAGS += -fexceptions

SHADOWTALK_DEBUG_ENABLE=YES
win32:QMAKE_LFLAGS += /NODEFAULTLIB:libcmtd.lib

INCLUDEPATH += include
INCLUDEPATH += src/core
INCLUDEPATH += src/net
INCLUDEPATH += src/widget

# Default rules for deployment.
#include(deployment.pri)


HEADERS += \
    include/peersafe/imapi/im.h \
    include/qrencode.h \
    include/maidsafe/common/active.h \
    src/net/st_net.h \
    src/core/st_cache.h \
    src/core/st_pixelsize.h \
    src/core/st_parsexml.h \
    src/core/st_log.h \
    src/core/st_context.h \
    src/core/st_qrcode.h \
    src/core/st_thread.h \
    src/core/st_zebra.h \
    src/core/st_base64.h \
    src/widget/st_utils.h \
    src/widget/st_friend.h \
    src/widget/st_message.h \
    src/widget/st_login.h \
    src/widget/st_group.h \
    src/widget/st_trayicon.h \
    src/widget/st_chat.h \
    src/widget/st_voice.h \
    src/widget/st_picture.h \
    src/widget/st_search.h
	
SOURCES += \
    src/main.cpp \
    src/net/st_net.cpp \
    src/core/st_cache.cpp \
    src/core/st_log.cpp \
    src/core/st_parsexml.cpp \
    src/core/st_pixelsize.cpp \
    src/core/st_zebra.cpp \
    src/core/st_context.cpp \
    src/core/st_base64.cpp \
    src/core/st_qrcode.cpp \
    src/core/st_thread.cpp \
    src/widget/st_utils.cpp \
    src/widget/st_friend.cpp \
    src/widget/st_group.cpp \
    src/widget/st_login.cpp \
    src/widget/st_message.cpp \
    src/widget/st_trayicon.cpp \
    src/widget/st_chat.cpp \
    src/widget/st_voice.cpp \
    src/widget/st_picture.cpp \
    src/widget/st_search.cpp
   
win32 {
    contains(SHADOWTALK_DEBUG_ENABLE, YES) {
        LIBS += -L$$PWD/lib/x32/debug/boost/     -lboost_chrono-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -lboost_date_time-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -lboost_filesystem-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -lboost_program_options-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -lboost_regex-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -lboost_system-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/boost/     -lboost_thread-vc120-mt-gd-1_57
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lcryptopp
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lmaidsafe_common
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lmaidsafe_passport
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_channel
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_imapi
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_nat
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_network
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_visit
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lpeersafe_oudp
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -lprotobuf_lite
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -ltorrent-rasterbar
        LIBS += -L$$PWD/lib/x32/debug/peersafe/  -ludt
        LIBS += -L$$PWD/lib/x32/debug/qrcode/    -lqrcode
    } else {
        LIBS += -L$$PWD/lib/x32/release/boost/     -lboost_chrono-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -lboost_date_time-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -lboost_filesystem-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -lboost_program_options-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -lboost_regex-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -lboost_system-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/boost/     -lboost_thread-vc120-mt-1_57
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lcryptopp-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lmaidsafe_common-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lmaidsafe_passport-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_channel-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_imapi-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_oudp-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_nat-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_network-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lpeersafe_visit-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -lprotobuf_lite-msr
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -ltorrent-rasterbar
        LIBS += -L$$PWD/lib/x32/release/peersafe/  -ludt-msr
        LIBS += -L$$PWD/lib/x32/release/qrcode/    -lqrcode
    }
} else {
    macx {
        LIBS += -dead_strip
        LIBS += -L$$PWD/lib/osx/boost/     -lboost_chrono-mt
        LIBS += -L$$PWD/lib/osx/boost/     -lboost_date_time-mt
        LIBS += -L$$PWD/lib/osx/boost/     -lboost_filesystem-mt
        LIBS += -L$$PWD/lib/osx/boost/     -lboost_program_options-mt
        LIBS += -L$$PWD/lib/osx/boost/     -lboost_regex-mt
        LIBS += -L$$PWD/lib/osx/boost/     -lboost_system-mt
        LIBS += -L$$PWD/lib/osx/boost/     -lboost_thread-mt
        LIBS += -L$$PWD/lib/osx/peersafe/  -lcryptopp
        LIBS += -L$$PWD/lib/osx/peersafe/  -lmaidsafe_common
        LIBS += -L$$PWD/lib/osx/peersafe/  -lmaidsafe_passport
        LIBS += -L$$PWD/lib/osx/peersafe/  -lpeersafe_channel
        LIBS += -L$$PWD/lib/osx/peersafe/  -lpeersafe_imapi
        LIBS += -L$$PWD/lib/osx/peersafe/  -lpeersafe_oudp
        LIBS += -L$$PWD/lib/osx/peersafe/  -lpeersafe_nat
        LIBS += -L$$PWD/lib/osx/peersafe/  -lpeersafe_network
        LIBS += -L$$PWD/lib/osx/peersafe/  -lpeersafe_visit
        LIBS += -L$$PWD/lib/osx/peersafe/  -lprotobuf_lite
        LIBS += -L$$PWD/lib/osx/peersafe/  -ltorrent-rasterbar
        LIBS += -L$$PWD/lib/osx/peersafe/  -ludt
        LIBS += -L$$PWD/lib/osx/qrencode/  -lqrencode
        
        #QMAKE_POST_LINK = ~/qt/5.5/clang_64/bin/macdeployqt $(TARGET_BUILD_DIR)/$(EXECUTABLE_PATH) -qmldir=$$PWD/qml/ -verbose=2
    } else {

    }
}


