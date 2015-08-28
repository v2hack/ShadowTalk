#-------------------------------------------------
#
# Project created by QtCreator 2015-08-27T18:20:58
#
#-------------------------------------------------

QT       -= gui

TARGET = libqrcode
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    bitstream.c \
    mask.c \
    mmask.c \
    mqrspec.c \
    qrencode.c \
    qrinput.c \
    qrspec.c \
    rscode.c \
    split.c

HEADERS += \
    bitstream.h \
    mask.h \
    mmask.h \
    mqrspec.h \
    qrencode.h \
    qrencode_inner.h \
    qrinput.h \
    qrspec.h \
    rscode.h \
    split.h \
    config.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
