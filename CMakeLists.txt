
project(ShadowTalk-PC)
cmake_minimum_required(VERSION 2.8.9)
# Find includes in corresponding build directories

MESSAGE(STATUS "${PROJECT_NAME}")
MESSAGE(STATUS "${CMAKE_SOURCE_DIR}")

#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")
MESSAGE(STATUS "peersafe_""${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

OPTION(USE_QT5 TRUE "Build with qt5")
OPTION(ENABLE_TESTING FALSE "Enable the unit tests")

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32 AND MSVC)    
	if(CMAKE_CL_64)
		set(QT5_PATH "D:/Qt/Qt5.5.0/5.5/msvc2013/")
		set(VSREDIST "vcredist_x64.exe")
	else()
	    MESSAGE(STATUS "WIN32,GO:"${WIN32})
		set(QT5_PATH "D:/Qt/Qt5.5.0/5.5/msvc2013/")
		SET(sha_talk_lib "D:/0010GitHub/dev/dev/ShadowTalkPC/lib/x32/release/")
		set(VSREDIST "vcredist_x86.exe")
	endif()
	set(USE_QT5 TRUE)
	set(CMAKE_PREFIX_PATH "D:/Qt/Qt5.5.0/Tools/QtCreator/bin/")
endif()

set(Qt5Core_DIR "${CMAKE_PREFIX_PATH}")
SET (Qt5Widgets_DIR "${QT5_PATH}lib/cmake/Qt5Widgets/")
SET( Qt5LinguistTools_DIR "${QT5_PATH}lib/cmake/Qt5LinguistTools/")
MESSAGE(STATUS "begin to find pakage ")
#用Qt5Widgets需要把所有相关支持DLL都找到并根据提示放到指定位置，这个过程比较麻烦；
find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools REQUIRED)


macro (FindQtLibs Target)	
		set (CMAKE_INCLUDE_CURRENT_DIR ON)		
		MESSAGE(STATUS "my qt current path:"${CMAKE_INCLUDE_CURRENT_DIR})
		FIND_PACKAGE(Qt5Widgets QUIET) 	
		qt5_use_modules(${PROJECT_NAME} ${ARGN})	
endmacro ()

#include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
#include_directories(${Qt5Widgets_INCLUDE_DIRS} "D:/Qt/Qt5.5.0/5.5/msvc2013/lib/cmake/" "D:/Qt/Qt5.5.0/5.5/msvc2013/lib/")
include_directories(${Qt5Widgets_INCLUDE_DIRS} "${QT5_PATH}lib/")

SET (PEERSAFE_QT_LIB_PATH "${QT5_PATH}lib/")

MESSAGE(STATUS ${Qt5Widgets_INCLUDE_DIRS})
MESSAGE(STATUS "include path:"${QT_INCLUDES})
include_directories("${CMAKE_SOURCE_DIR}/include/" "${CMAKE_SOURCE_DIR}/src/qrcode/" "${CMAKE_SOURCE_DIR}/src/widget/")
include_directories("${CMAKE_SOURCE_DIR}/src/core/" "${CMAKE_SOURCE_DIR}/src/net/" )

#以下是为用编译第三方插件代码
#include_directories("${CMAKE_SOURCE_DIR}/include/boost/asio/" "${CMAKE_SOURCE_DIR}/include/boost/asio/impl/" "${CMAKE_SOURCE_DIR}/include/maidsafe/common/")
#include_directories("${CMAKE_SOURCE_DIR}/include/boost/windows/" )
 

set(ST_HDR
	${CMAKE_SOURCE_DIR}/src/main.cpp	
)
add_definitions(-DMAIDSAFE_WIN32)

set(ST_SRC  
 ${CMAKE_SOURCE_DIR}/include/im.h
 ${CMAKE_SOURCE_DIR}/src/core/st_log.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_log.h
 ${CMAKE_SOURCE_DIR}/src/core/st_parsexml.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_parsexml.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_picture.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_picture.h
 ${CMAKE_SOURCE_DIR}/src/core/st_pixelsize.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_pixelsize.h
 ${CMAKE_SOURCE_DIR}/src/core/st_qrcode.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_qrcode.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_search.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_search.h
 ${CMAKE_SOURCE_DIR}/src/core/st_thread.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_thread.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_voice.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_voice.h
 ${CMAKE_SOURCE_DIR}/src/core/st_zebra.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_zebra.h
 ${CMAKE_SOURCE_DIR}/src/main.cpp
 ${CMAKE_SOURCE_DIR}/src/net/st_net.cpp
 ${CMAKE_SOURCE_DIR}/src/net/st_net.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/bitstream.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/bitstream.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/config.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/mask.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/mask.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/mmask.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/mmask.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/mqrspec.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/mqrspec.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/qrencode.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/qrencode.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/qrencode_inner.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/qrinput.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/qrinput.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/qrspec.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/qrspec.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/rscode.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/rscode.h
 ${CMAKE_SOURCE_DIR}/src/qrcode/split.c
 ${CMAKE_SOURCE_DIR}/src/qrcode/split.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_chat.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_chat.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_friend.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_friend.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_group.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_group.cpp 
 ${CMAKE_SOURCE_DIR}/src/widget/st_utils.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_utils.h
 ${CMAKE_SOURCE_DIR}/src/core/st_cache.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_cache.h
 ${CMAKE_SOURCE_DIR}/src/core/st_context.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_context.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_login.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_login.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_message.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_message.h
 ${CMAKE_SOURCE_DIR}/src/widget/st_trayicon.cpp
 ${CMAKE_SOURCE_DIR}/src/widget/st_trayicon.h
 ${CMAKE_SOURCE_DIR}/src/core/st_base64.cpp
 ${CMAKE_SOURCE_DIR}/src/core/st_base64.h
)
set (RESOURCES ${CMAKE_SOURCE_DIR}/qml.qrc)

set(ST_RESOURCES
 ${CMAKE_SOURCE_DIR}/tools/arc.qml
 ${CMAKE_SOURCE_DIR}/tools/Drag.qml
 ${CMAKE_SOURCE_DIR}/tools/FlowEffect.qml
 ${CMAKE_SOURCE_DIR}/tools/ListViewTest.qml
 ${CMAKE_SOURCE_DIR}/tools/Mask.qml
 ${CMAKE_SOURCE_DIR}/tools/Popup.qml
 ${CMAKE_SOURCE_DIR}/tools/rotate.qml
 ${CMAKE_SOURCE_DIR}/tools/rotate2.qml
 ${CMAKE_SOURCE_DIR}/tools/test.cc
 ${CMAKE_SOURCE_DIR}/tools/TestPopup.qml
 ${CMAKE_SOURCE_DIR}/tools/Wheel.qml
 ${CMAKE_SOURCE_DIR}/tools/xuan1.qml
 ${CMAKE_SOURCE_DIR}/tools/xuan2.qml 
 ${CMAKE_SOURCE_DIR}/qml/ChatDisplay.qml
 ${CMAKE_SOURCE_DIR}/qml/ChatList.qml
 ${CMAKE_SOURCE_DIR}/qml/ChatTextInput.qml
 ${CMAKE_SOURCE_DIR}/qml/common.js
 ${CMAKE_SOURCE_DIR}/qml/js_st_emoji.js
 ${CMAKE_SOURCE_DIR}/qml/FriendAndContact.qml
 ${CMAKE_SOURCE_DIR}/qml/FriendList.qml
 ${CMAKE_SOURCE_DIR}/qml/login.qml
 ${CMAKE_SOURCE_DIR}/qml/LoginProcess.qml
 ${CMAKE_SOURCE_DIR}/qml/main.qml
 ${CMAKE_SOURCE_DIR}/qml/MainWindowButton.qml
 ${CMAKE_SOURCE_DIR}/qml/MainWindowSetting.qml
 ${CMAKE_SOURCE_DIR}/qml/picture.qml
 ${CMAKE_SOURCE_DIR}/qml/SearchList.qml	
${CMAKE_SOURCE_DIR}/qml/emoji/1f302.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f31f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f380.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f3a9.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f3bd.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f3c3.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f440.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f442.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f443.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f444.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f445.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f446.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f447.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f448.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f449.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f44a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f44b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f44c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f44d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f44e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f44f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f450.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f451.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f452.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f453.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f454.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f455.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f456.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f457.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f458.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f459.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f45a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f45b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f45c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f45d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f45e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f45f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f460.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f461.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f462.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f463.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f464.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f465.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f466.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f467.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f468.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f469.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f46a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f46b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f46c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f46d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f46e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f46f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f470.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f471.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f472.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f473.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f474.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f475.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f476.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f477.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f478.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f479.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f47a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f47c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f47d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f47f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f480.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f481.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f482.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f483.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f484.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f485.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f486.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f487.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f48b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f48c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f48d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f48e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f48f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f491.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f493.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f494.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f495.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f496.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f497.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f498.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f499.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f49a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f49b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f49c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f49e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4a2.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4a4.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4a5.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4a6.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4a7.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4a8.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4a9.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4aa.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4ab.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4ac.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4ad.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f4bc.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f525.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f600.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f601.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f602.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f603.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f605.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f606.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f607.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f608.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f609.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f60a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f60b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f60c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f60d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f60e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f60f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f610.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f611.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f612.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f613.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f614.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f615.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f616.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f617.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f618.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f619.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f61a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f61b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f61c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f61d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f61e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f61f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f620.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f621.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f622.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f623.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f624.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f625.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f626.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f627.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f628.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f629.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f62a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f62b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f62c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f62d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f62e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f62f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f630.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f631.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f632.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f633.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f634.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f635.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f636.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f637.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f638.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f639.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f63a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f63b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f63c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f63d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f63e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f63f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f640.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f645.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f646.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f647.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f648.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f649.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f64a.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f64b.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f64c.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f64d.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f64e.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f64f.png
${CMAKE_SOURCE_DIR}/qml/emoji/1f6b6.png
${CMAKE_SOURCE_DIR}/qml/emoji/261d.png
${CMAKE_SOURCE_DIR}/qml/emoji/263a.png
${CMAKE_SOURCE_DIR}/qml/emoji/270a.png
${CMAKE_SOURCE_DIR}/qml/emoji/270b.png
${CMAKE_SOURCE_DIR}/qml/emoji/270c.png
${CMAKE_SOURCE_DIR}/qml/emoji/2728.png
${CMAKE_SOURCE_DIR}/qml/emoji/2764.png

 ${CMAKE_SOURCE_DIR}/sound/event.wav
 ${CMAKE_SOURCE_DIR}/sound/message.wav
 ${CMAKE_SOURCE_DIR}/sound/online.mp3 
 ${CMAKE_SOURCE_DIR}/img/brower/st_pic_close.png
 ${CMAKE_SOURCE_DIR}/img/brower/st_pic_last.png
 ${CMAKE_SOURCE_DIR}/img/brower/st_pic_next.png
 ${CMAKE_SOURCE_DIR}/img/brower/st_pic_roll.png
 ${CMAKE_SOURCE_DIR}/img/brower/st_pic_save.png
 ${CMAKE_SOURCE_DIR}/img/choice/st_chat_list.png
 ${CMAKE_SOURCE_DIR}/img/choice/st_choice_button.png
 ${CMAKE_SOURCE_DIR}/img/choice/st_contact_list.png
 ${CMAKE_SOURCE_DIR}/img/head/st_ball_white.png
 ${CMAKE_SOURCE_DIR}/img/head/st_message_frame.png
 ${CMAKE_SOURCE_DIR}/img/head/st_message_point.png
 ${CMAKE_SOURCE_DIR}/img/sound/st_m_sound_1.png
 ${CMAKE_SOURCE_DIR}/img/sound/st_m_sound_11.png
 ${CMAKE_SOURCE_DIR}/img/sound/st_m_sound_2.png
 ${CMAKE_SOURCE_DIR}/img/sound/st_m_sound_22.png
 ${CMAKE_SOURCE_DIR}/img/sound/st_m_sound_3.png
 ${CMAKE_SOURCE_DIR}/img/sound/st_m_sound_33.png
 ${CMAKE_SOURCE_DIR}/img/st_button_close_1.png
 ${CMAKE_SOURCE_DIR}/img/st_button_close_2.png
 ${CMAKE_SOURCE_DIR}/img/st_button_max_1.png
 ${CMAKE_SOURCE_DIR}/img/st_button_max_2.png
 ${CMAKE_SOURCE_DIR}/img/st_button_min_1.png
 ${CMAKE_SOURCE_DIR}/img/st_button_min_2.png
 ${CMAKE_SOURCE_DIR}/img/st_button_normal_1.png
 ${CMAKE_SOURCE_DIR}/img/st_button_normal_2.png
 ${CMAKE_SOURCE_DIR}/img/st_button_search.png
 ${CMAKE_SOURCE_DIR}/img/st_chat_delivery.png
 ${CMAKE_SOURCE_DIR}/img/st_chat_expression.png
 ${CMAKE_SOURCE_DIR}/img/st_chat_screenshot.png
 ${CMAKE_SOURCE_DIR}/img/st_green_point.png
 ${CMAKE_SOURCE_DIR}/img/st_icon.png
 ${CMAKE_SOURCE_DIR}/img/st_qr_code.png
 ${CMAKE_SOURCE_DIR}/img/st_qr_hint.png
 ${CMAKE_SOURCE_DIR}/img/st_qr_point.png
 ${CMAKE_SOURCE_DIR}/img/st_qr_process.png
 ${CMAKE_SOURCE_DIR}/img/st_select_chat.png
 ${CMAKE_SOURCE_DIR}/img/st_select_chat_t.png
 ${CMAKE_SOURCE_DIR}/img/st_select_users.png
 ${CMAKE_SOURCE_DIR}/img/st_select_users_t.png
 ${CMAKE_SOURCE_DIR}/img/st_setting.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_exit_1.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_exit_2.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_lock_screen_1.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_lock_screen_2.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_no_sound_1.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_no_sound_2.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_sound_1.png
 ${CMAKE_SOURCE_DIR}/img/st_setting_sound_2.png
 ${CMAKE_SOURCE_DIR}/img/st_white_point.png
 ${CMAKE_SOURCE_DIR}/translations/zh.ts 
 ${CMAKE_SOURCE_DIR}/qml/functions.js 
 ${CMAKE_SOURCE_DIR}/qml.qrc
 ${CMAKE_SOURCE_DIR}/res/fonts/KhmerUI.ttf
 ${CMAKE_SOURCE_DIR}/res/fonts/KhmerUIb.ttf
 ${CMAKE_SOURCE_DIR}/res/fonts/fangzheng_gbk.ttf
 ${CMAKE_SOURCE_DIR}/res/settrings.ini

)

SET(peersafe_lib 	  
 ${CMAKE_SOURCE_DIR}/lib/x32/release/boost/libboost_chrono-vc120-mt-1_57.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/boost/libboost_date_time-vc120-mt-1_57.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/boost/libboost_filesystem-vc120-mt-1_57.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/boost/libboost_program_options-vc120-mt-1_57.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/boost/libboost_regex-vc120-mt-1_57.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/boost/libboost_system-vc120-mt-1_57.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/boost/libboost_thread-vc120-mt-1_57.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/ice/libpj.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/ice/libpjlib-util.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/ice/libpjnath.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/cryptopp-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/maidsafe_common-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/maidsafe_passport-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/peersafe_channel-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/peersafe_imapi-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/peersafe_nat-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/peersafe_network-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/peersafe_oudp-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/peersafe_visit-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/protobuf-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/protobuf_lite-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/proto_compiler-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/torrent-rasterbar.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/peersafe/udt-msr.lib
 ${CMAKE_SOURCE_DIR}/lib/x32/release/qrcode/libqrcode.lib
 ) 
#${QT5_PATH}/plugins/audio/
SET(PEERSAFE_QT_LIB 	
	${PEERSAFE_QT_LIB_PATH}/Qt5Multimedia.lib
	${PEERSAFE_QT_LIB_PATH}/Qt5Qml.lib
	${PEERSAFE_QT_LIB_PATH}/Qt5Quick.lib
	${PEERSAFE_QT_LIB_PATH}/Qt5Core.lib
	${PEERSAFE_QT_LIB_PATH}/Qt5Network.lib
	${PEERSAFE_QT_LIB_PATH}/Qt5Xml.lib
	${PEERSAFE_QT_LIB_PATH}/Qt5Widgets.lib
	)
#因为需要用QT5_ADD_RESOURCES这个函数，需要先调用FIND_PACKAGE(Qt5Widgets);
QT5_ADD_RESOURCES (RCC ${RESOURCES})


find_package(Qt5Widgets)
set (LC_EXEC_SUFFIX "-qt5")
add_executable(${PROJECT_NAME}
	    ${RESOURCES}
		${ST_HDR}
		${ST_SRC}
		${RCC}
		${ST_RESOURCES}
		${ST_FORM_HDR}			
		)
qt5_use_modules(${PROJECT_NAME} Widgets Quick Qml Core Network Xml Multimedia)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} Qt5::Widgets Qt5::Quick Qt5::Qml Qt5::Core Qt5::Network Qt5::Xml Qt5::Multimedia)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${PEERSAFE_QT_LIB})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${peersafe_lib})
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} 		
#		${QT_LIBRARIES}
#		${WIN32_STATIC_LINK}		
#		${ADDITIONAL_LIBS})

MESSAGE(STATUS "编后的路径:"${PROJECT_BINARY_DIR})
#以下一行代码只能在windows下运行；
EXECUTE_PROCESS(COMMAND CMD /c ${QT5_PATH}/bin/windeployqt.exe ${PROJECT_BINARY_DIR}/Release/${PROJECT_NAME}.exe -qmldir ${QT5_PATH}/qml/  RESULT_VARIABLE rv)

#foreach(plugin ${Qt5Network_PLUGINS})
#  get_target_property(_loc ${plugin} LOCATION)
#  message("Plugin ${plugin} is at location ${_loc}")
#endforeach()