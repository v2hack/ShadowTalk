/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: ShawdowTalk-PC主文件
 *  简要描述: 程序启动主文件
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include <QApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QtQuick/QQuickView>
#include <QtQml>
#include <QThread>

#include <iostream>
#include <fstream>
#include <stdint.h>

#include "peersafe/imapi/im.h"
#include "st_pixelsize.h"
#include "st_friend.h"
#include "st_group.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_utils.h"
#include "st_login.h"
#include "st_message.h"
#include "st_zebra.h"
#include "st_net.h"
#include "st_log.h"
#include "st_voice.h"
#include "st_picture.h"
#include "st_qrcode.h"
#include "st_thread.h"
#include "st_trayicon.h"

peersafe::im::Message_client *zebraClient = new peersafe::im::Message_client();
zebraDeleagates zebarDele;

/* 全局上下文 */
struct ShadowTalkContext gCtx;

/**
 *  功能描述: 设置启动参数
 *  @param  无
 *
 *  @return 无
 */
void setAppParameter()
{
    /* 设置程序路径 */
    QString dir = QGuiApplication::applicationDirPath();
    qDebug() << "c++: application current dir - " << dir;
    QDir::setCurrent(dir);
    /* 库加载路径 */
    //QGuiApplication::addLibraryPath("./plugins");

    /* 创建工作目录 */
    QDir workDir(dir + "/temp");
    if (!workDir.exists()) {
        workDir.mkdir(dir + "/temp");
    } else {

    }
    return;
}

/**
 *  功能描述: 注册QML类型
 *  @param  无
 *
 *  @return 无
 */
void registerQmlTye()
{
    /* 注册C++类型到QML */
    qmlRegisterType<PointSizeToPixelSize>("st.font.PointSizeToPixelSize", 1, 0, "PointSizeToPixelSize");
    qmlRegisterType<MessageManager>("st.info.MessageManager", 1, 0, "MessageManager");
    qmlRegisterType<SelectFriend>("st.info.SelectFriend", 1, 0, "SelectFriend");
    qmlRegisterType<SelectGroup>("st.info.SelectGroup", 1, 0, "SelectGroup");
    qmlRegisterType<Voice>("st.info.Voice", 1, 0, "Voice");
    qmlRegisterType<NormalPicture>("st.info.NormalPicture", 1, 0, "NormalPicture");
    qmlRegisterType<WindowClose>("st.info.WindowClose", 1, 0, "WindowClose");
    qmlRegisterType<GoSearch>("st.info.GoSearch", 1, 0, "GoSearch");
    return;
}

/**
 *  功能描述: 注册QML属性
 *  @param viewer       窗口参数变量
 *
 *  @return 无
 */
void registerQMlProperty(QQuickView &viewer)
{
    /* 注册C++类型到QML为属性 */
    viewer.rootContext()->setContextProperty("ShadowTalkCache", gCtx.cache);
    return;
}

/**
 *  功能描述: 设置viewer参数
 *  @param viewer       窗口参数变量
 *  @param qmlProperty  qml属性变量
 *  @param qmlFile      qml源文件
 *
 *  @return 无
 */
void setViewerParameter(QQuickView &viewer, QString qmlProperty, QString qmlFile)
{
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(qmlFile));

    /* 设置无边框及透明 */
    viewer.setFlags(Qt::FramelessWindowHint | Qt::Window);
    viewer.setColor(QColor(Qt::transparent));

    /* viewer注册到qml */
    QQmlContext *qmlContext = viewer.rootContext();
    if (qmlContext) {
        qmlContext->setContextProperty(qmlProperty, &viewer);
    }
    return;
}

/**
 *  功能描述: 设置主窗口viewer
 *  @param viewer   窗口参数变量
 *
 *  @return 无
 */
void createBaseViewer(QQuickView &viewer)
{
    gCtx.viewer_ = &viewer;
    setViewerParameter(viewer, "mainwindow", "qrc:/qml/main.qml");
    viewer.hide();
    return;
}

/**
 *  功能描述: 登陆窗口viewer
 *  @param viewer   窗口参数变量
 *
 *  @return 无
 */
void createLoginViewer(QQuickView &viewer)
{
    gCtx.loginer_ = &viewer;
    setViewerParameter(viewer, "loginwindow", "qrc:/qml/login.qml");
    /* 生成二维码并显示到界面上 */
    if (Login::ShadowTalkLogin() < 0) {
        qDebug() << "c++: create sync qrchannel fail";
    }
    viewer.show();
    return;
}

/**
 *  功能描述: 缓存初始化
 *  @param  无
 *
 *  @return 无
 */
void createCache()
{
    gCtx.cache = new Cache;
    if (!gCtx.cache) {
        exit(0);
    }
    return;
}


/**
 *  功能描述: 初始化impai层参数
 *  @param 无
 *
 *  @return
 */
void initZebraEngine()
{
    gCtx.zebra_    = zebraClient;
    gCtx.delegate_ = &zebarDele;

    gCtx.conf.soundEnable  = true;
    gCtx.conf.reciveEnable = true;

    gCtx.windowFlag_ = gCtx.changeFlag_ = gCtx.loadXmlFlag_ = 0;
    gCtx.threadStop_ = 0;
    gCtx.phoneUpdateTime.start();

//    zebraClient->init("0.0.0.0:49987 107.150.98.47:27053 52.68.228.63:27054 54.169.92.238:27053 45.32.70.172:27053 182.254.219.210:27054 182.254.219.210:27055 123.56.156.198:27054 115.159.70.71:27054", &zebarDele, "17monipdb.dat");
    zebraClient->init("0.0.0.0:49987 192.168.0.140:27053", &zebarDele, "17monipdb.dat");
    //zebraClient->enableLog();
    qDebug() << "c++: init zebra engine success";
    return;
}

/**
 *  功能描述: 主函数
 *  @param argc   入参数量
 *  @param argv   参数列表
 *
 *  @return
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    memset(&gCtx, 0, sizeof(gCtx));
    gCtx.app_ = &app;

    /* 缓存 */
    createCache();

    /* 设置启动参数 */
    setAppParameter();
    initZebraEngine();

    /* 注册QML */
    registerQmlTye();

    /* 聊天主界面 */
    QQuickView viewer;
    createBaseViewer(viewer);
    gCtx.tray_ = new TrayIcon(&viewer);
    //gCtx.tray_->onRemind("hello world");

    /* 登录主页面 */
    QQuickView loginer;
    createLoginViewer(loginer);

    /* 界面切换线程 */
    Sthread tid(&gCtx);
    tid.run();

    return app.exec();
}
