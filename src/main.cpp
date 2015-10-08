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

#include "im.h"

#include "st_pixelsize.h"
#include "st_friend.h"
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
void setAppParameter() {
    /* 设置程序路径 */
    QString dir = QGuiApplication::applicationDirPath();
    qDebug() << "Application current dir - " << dir;
    QDir::setCurrent(dir);
    /* 库加载路径 */
    QGuiApplication::addLibraryPath("./plugins");

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
void registerQmlTye() {
    /* 注册C++类型到QML */
    qmlRegisterType<PointSizeToPixelSize>("st.font.PointSizeToPixelSize", 1, 0, "PointSizeToPixelSize");
    qmlRegisterType<MessageManager>("st.info.MessageManager", 1, 0, "MessageManager");
    qmlRegisterType<SelectFriend>("st.info.SelectFriend", 1, 0, "SelectFriend");
    qmlRegisterType<Voice>("st.info.Voice", 1, 0, "Voice");
    qmlRegisterType<NormalPicture>("st.info.NormalPicture", 1, 0, "NormalPicture");
    return;
}

/**
 *  功能描述: 注册QML属性
 *  @param viewer       窗口参数变量
 *
 *  @return 无
 */
void registerQMlProperty(QQuickView &viewer) {
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
void setViewerParameter(QQuickView &viewer, QString qmlProperty, QString qmlFile) {
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
void createBaseViewer(QQuickView &viewer) {
    gCtx.viewer = &viewer;
    setViewerParameter(viewer, "mainwindow", "qrc:/qml/main.qml");
    viewer.hide();
}

/**
 *  功能描述: 登陆窗口viewer
 *  @param viewer   窗口参数变量
 *
 *  @return 无
 */
void createLoginViewer(QQuickView &viewer) {
    gCtx.loginer = &viewer;
    setViewerParameter(viewer, "loginwindow", "qrc:/qml/login.qml");

    /* 生成二维码并显示到界面上 */
    if (ShadowTalkLogin() < 0) {
        qDebug() << "create sync qrchannel fail";
    }
    viewer.show();
}

/**
 *  功能描述: 缓存初始化
 *  @param  无
 *
 *  @return 无
 */
void createCache() {
    gCtx.cache = new Cache;
    if (!gCtx.cache) {
        exit(0);
    }
}


/**
 *  功能描述: 初始化impai层参数
 *  @param 无
 *
 *  @return
 */
void initZebraEngine() {

    gCtx.zebra    = zebraClient;
    gCtx.delegate = &zebarDele;

    gCtx.conf.soundEnable  = true;
    gCtx.conf.reciveEnable = true;

    gCtx.windowFlag = gCtx.changeFlag = 0;
    gCtx.phoneUpdateTime.start();

    zebraClient->init("127.0.0.1:6000 120.27.42.174:27053", &zebarDele, "17monipdb.dat");
    qDebug() << "[imapi] << init zebra engine success";
    return;
}

#include "st_thread.h"
#include "st_trayicon.h"

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
    gCtx.app = &app;

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
    gCtx.tray = new TrayIcon(&viewer);
    gCtx.tray->onRemind("hello world");

    /* 登录主页面 */
    QQuickView loginer;
    createLoginViewer(loginer);

    /* 界面切换线程 */
    Sthread tid(&gCtx);
    tid.run();

    return app.exec();
}
