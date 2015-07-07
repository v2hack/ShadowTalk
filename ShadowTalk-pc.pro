#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T17:40:16
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShadowTalk-pc
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -fno-exceptions

INCLUDEPATH += include
INCLUDEPATH += src/core
INCLUDEPATH += src/net
INCLUDEPATH += src/widget

HEADERS += \
        include/mainwindow.h \
        src/core/core.h \
        src/net/net.h \
        src/widget/friend_list_layout.h \
        src/widget/group_widget.h \
        src/widget/login.h \
        src/widget/style.h \
        src/widget/widget.h \
        src/widget/friend_widget.h \
        src/widget/gui.h \
        src/widget/qr_widget.h \
        src/widget/system_tray_icon.h

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/core/core.cpp \
        src/net/net.cpp \
        src/widget/friend_list_layout.cpp \
        src/widget/group_widget.cpp \
        src/widget/login.cpp \
        src/widget/style.cpp \
        src/widget/widget.cpp \
        src/widget/friend_widget.cpp \
        src/widget/gui.cpp \
        src/widget/qr_widget.cpp \
        src/widget/system_tray_icon.cpp

FORMS += \
        ./ui/mainwindow.ui
