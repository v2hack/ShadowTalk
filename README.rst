Qt for ShawdowTalk with c++11 & boost

libqrencode
<dev>/qrencode-3.4.4.zip
$ cd qrencode-3.4.4
$ ./configure --enable-static --without-tools
$ make
$ cp .libs/libqrencode.a <shadowtalkPC>/lib/osx/qrencode/libqrencode.a

------------------MacOSx-------------------------------
qmakexcode
~/qt/5.5/clang_64/bin/qmake -spec macx-xcode ShadowTalk-PC.pro

~/qt/5.5/clang_64/bin/qmake -config release -spec macx-xcode ShadowTalk-PC.pro

#首先用xode生成ShadowTalk.app
#把依赖的framework和plugin拷贝进ShadowTalk.ap
~/qt/5.5/clang_64/bin/macdeployqt ShadowTalk.app -qmldir=../qml

生成dmg格式包
~/qt/5.5/clang_64/bin/macdeployqt ShadowTalk.app -dmg


------------------WIN32-------------------------------
用qmake生成vistual studio项目
qmake -tp vc




------------------MacOSx 不使用macdeployqt打包-------------------------------
#查看ShadowTalk.app的依赖包
otool -L ShadowTalk.app/Contents/MacOS/ShadowTalk
#重新命名framework id
install_name_tool -id @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtCore.framework/Versions/5/QtCore
install_name_tool -id @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ShadowTalk.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
install_name_tool -id @executable_path/../Frameworks/QtQuick.framework/Versions/5/QtQuick ShadowTalk.app/Contents/Frameworks/QtQuick.framework/Versions/5/QtQuick
install_name_tool -id @executable_path/../Frameworks/QtQml.framework/Versions/5/QtQml ShadowTalk.app/Contents/Frameworks/QtQml.framework/Versions/5/QtQml
install_name_tool -id @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ShadowTalk.app/Contents/Frameworks/QtNetwork.framework/Versions/5/QtNetwork
install_name_tool -id @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ShadowTalk.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets
install_name_tool -id @executable_path/../Frameworks/QtMultimedia.framework/Versions/5/QtMultimedia ShadowTalk.app/Contents/Frameworks/QtMultimedia.framework/Versions/5/QtMultimedia
install_name_tool -id @executable_path/../Frameworks/QtXml.framework/Versions/5/QtXml ShadowTalk.app/Contents/Frameworks/QtXml.framework/Versions/5/QtXml
install_name_tool -id @executable_path/../Frameworks/QtDBus.framework/Versions/5/QtDBus ShadowTalk.app/Contents/Frameworks/QtDBus.framework/Versions/5/QtDBus
install_name_tool -id @executable_path/../Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport ShadowTalk.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport
#替换ShadowTalk依赖的framework id
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/MacOs/ShadowTalk
install_name_tool -change @rpath/QtGui.framework/Versions/5/QtGui   @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ShadowTalk.app/Contents/MacOs/ShadowTalk
install_name_tool -change @rpath/QtQuick.framework/Versions/5/QtQuick @executable_path/../Frameworks/QtQuick.framework/Versions/5/QtQuick ShadowTalk.app/Contents/MacOs/ShadowTalk
install_name_tool -change @rpath/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml.framework/Versions/5/QtQml ShadowTalk.app/Contents/MacOs/ShadowTalk
install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ShadowTalk.app/Contents/MacOs/ShadowTalk
install_name_tool -change @rpath/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ShadowTalk.app/Contents/MacOs/ShadowTalk
install_name_tool -change @rpath/QtMultimedia.framework/Versions/5/QtMultimedia @executable_path/../Frameworks/QtMultimedia.framework/Versions/5/QtMultimedia ShadowTalk.app/Contents/MacOs/ShadowTalk
install_name_tool -change @rpath/QtXml.framework/Versions/5/QtXml @executable_path/../Frameworks/QtXml.framework/Versions/5/QtXml ShadowTalk.app/Contents/MacOs/ShadowTalk

#查看QtGui.framework的依赖包
otool -L ShadowTalk.app/Contents/Frameworks/QtGui.framework/QtGui
#替换QtGui.framework依赖的framework id
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtGui.framework/Versions/5/QtGui
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtQuick.framework/Versions/5/QtQuick
install_name_tool -change @rpath/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ShadowTalk.app/Contents/Frameworks/QtQuick.framework/Versions/5/QtQuick
install_name_tool -change @rpath/QtQml.framework/Versions/5/QtQml @executable_path/../Frameworks/QtQml.framework/Versions/5/QtQml ShadowTalk.app/Contents/Frameworks/QtQuick.framework/Versions/5/QtQuick
install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ShadowTalk.app/Contents/Frameworks/QtQuick.framework/Versions/5/QtQuick
install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ShadowTalk.app/Contents/Frameworks/QtQml.framework/Versions/5/QtQml
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtQml.framework/Versions/5/QtQml
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtNetwork.framework/Versions/5/QtNetwork
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets
install_name_tool -change @rpath/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ShadowTalk.app/Contents/Frameworks/QtWidgets.framework/Versions/5/QtWidgets
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtMultimedia.framework/Versions/5/QtMultimedia
install_name_tool -change @rpath/QtNetwork.framework/Versions/5/QtNetwork @executable_path/../Frameworks/QtNetwork.framework/Versions/5/QtNetwork ShadowTalk.app/Contents/Frameworks/QtMultimedia.framework/Versions/5/QtMultimedia
install_name_tool -change @rpath/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ShadowTalk.app/Contents/Frameworks/QtMultimedia.framework/Versions/5/QtMultimedia
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtXml.framework/Versions/5/QtXml
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtDBus.framework/Versions/5/QtDBus
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport
install_name_tool -change @rpath/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ShadowTalk.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport
install_name_tool -change @rpath/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ShadowTalk.app/Contents/Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport
install_name_tool -change @rpath/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui ShadowTalk.app/Contents/PlugIns/platforms/libqcocoa.dylib
install_name_tool -change @rpath/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore ShadowTalk.app/Contents/PlugIns/platforms/libqcocoa.dylib
install_name_tool -change @rpath/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets ShadowTalk.app/Contents/PlugIns/platforms/libqcocoa.dylib
install_name_tool -change @rpath/QtDBus.framework/Versions/5/QtDBus @executable_path/../Frameworks/QtDBus.framework/Versions/5/QtDBus ShadowTalk.app/Contents/PlugIns/platforms/libqcocoa.dylib
install_name_tool -change @rpath/QtPrintSupport.framework/Versions/5/QtPrintSupport @executable_path/../Frameworks/QtPrintSupport.framework/Versions/5/QtPrintSupport ShadowTalk.app/Contents/PlugIns/platforms/libqcocoa.dylib



