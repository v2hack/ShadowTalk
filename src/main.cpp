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
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml>

#include <iostream>

#include "st_pixelsize.h"
#include "st_friend.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_utils.h"
#include "st_login.h"
#include "st_message.h"
#include "im.h"
#include "st_zebra.h"
#include "st_net.h"
#include "st_parsexml.h"

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

#include <fstream>
#include <stdint.h>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

namespace fs = boost::filesystem;

/* 测试使用 */
int parseEncryptXml(QString fileName, QString passwd) {
    QString qPlainData;

    std::string sPasswd = passwd.toStdString();
    std::string sDecryptData;
    std::string sPlainData;
    std::string sEncryptData;
    ParseXml xml;

    /* 读入文件 */
    std::ifstream file;
    file.open(fileName.toStdString().c_str(), std::ios::in | std::ios::binary);
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);
    char *buffer = new char[length];
    if (!buffer) {
        return -1;
    }
    file.read(buffer, length);
    sEncryptData.assign(buffer, length);

    /* 开始解密 */
    sDecryptData = zebraClient->decrypt(sEncryptData, sPasswd);
    if (sDecryptData.empty()) {
        qDebug() << "xml: decrypt xml file fail";
		return -1;
    }
    qDebug() << "decrypt file ok";

    /* 开始解压 */
    sPlainData = gCtx.zebra->gzipUncompress(sDecryptData);
    if (sPlainData.empty()) {
        qDebug() << "xml: unzip xml file fail";
        return -1;
    }
    qDebug() << "uncompress file ok";

    qPlainData = QString::fromStdString(sPlainData);
    if (xml.parseDencryptXml(qPlainData) < 0){
        return -1;
    }
    return 0;


    //    QSettings *settings = new QSettings("list.ini", QSettings::IniFormat);

    //    QString friend1 = settings->value("friend1").toString();
    //    Friend *f1 = new Friend(friend1, gCtx.cache->getNextIndex());
    //    gCtx.cache->insertOneFriend(f1);
    //    qDebug() << "add friend - " << friend1;

    //    QString friend2 = settings->value("friend2").toString();
    //    Friend *f2 = new Friend(friend2, gCtx.cache->getNextIndex());
    //    gCtx.cache->insertOneFriend(f2);

    //    QString friend3 = settings->value("friend3").toString();
    //    Friend *f3 = new Friend(friend3, gCtx.cache->getNextIndex());
    //    gCtx.cache->insertOneFriend(f3);

    //    QString friend4 = settings->value("friend4").toString();
    //    Friend *f4 = new Friend(friend4, gCtx.cache->getNextIndex());
    //    gCtx.cache->insertOneFriend(f4);
    //    return;
}



void initZebraEngine() {
    gCtx.zebra = zebraClient;
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
    QGuiApplication app(argc, argv);
    gCtx.app = &app;

    /* 设置启动参数 */
    setAppParameter();
    initZebraEngine();

    /* 注册QML */
    registerQmlTye();

    /* 聊天主界面 */
    QQuickView viewer;
    createBaseViewer(viewer);

    /* 登录主页面 */
    QQuickView loginer;
    createLoginViewer(loginer);

    /* 缓存 */
    createCache();

    for (int i = 0 ; i < 360; i++) {
        ShadowTalkSleep(1);
        ShadowTalkSetSyncProcess(i);
    }

    /* 界面交换 */
    loginer.hide();
    viewer.show();

    getLocalIp();


    ShadowTalkSleep(5);
    /* 加载XML文件 */
    if (parseEncryptXml(QString("shadowSecret"), QString("SHADOWTALK1")) < 0) {
        std::cout << "parse xml fail" << std::endl;
        return -1;
    }

    return app.exec();
}
