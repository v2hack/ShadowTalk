TEMPLATE = app

QT += qml quick

#SOURCES += main.cpp


CONFIG += c++11
QMAKE_CXXFLAGS += -fno-exceptions

INCLUDEPATH += include
INCLUDEPATH += src/core
INCLUDEPATH += src/net
INCLUDEPATH += src/widget

HEADERS += \
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


RESOURCES += qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
