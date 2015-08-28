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
#include "st_parsexml.h"
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
 *  功能描述: 解析xml文件
 *  @param fileName   文件名
 *  @param passwd     解密密码
 *
 *  @return
 */
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
        slog("func<%s> : msg<%s> para<file - %s, pwd - %s>\n",
             "parseEncryptXml", "decrypt xml file fail",
             fileName.toStdString().c_str(), passwd.toStdString().c_str());
        return -1;
    }
    slog("func<%s> : msg<%s> para<file - %s, pwd - %s>\n",
         "parseEncryptXml", "decrypt xml file success",
         fileName.toStdString().c_str(), passwd.toStdString().c_str());

    /* 开始解压 */
    sPlainData = gCtx.zebra->gzipUncompress(sDecryptData);
    if (sPlainData.empty()) {
        slog("func<%s> : msg<%s> para<file - %s>\n",
             "parseEncryptXml", "uncompress xml file fail", fileName.toStdString().c_str());
        return -1;
    }
    slog("func<%s> : msg<%s> para<file - %s>\n",
         "parseEncryptXml", "uncompress xml file success", fileName.toStdString().c_str());

    qPlainData = QString::fromStdString(sPlainData);
    if (xml.parseDencryptXml(qPlainData) < 0){
        return -1;
    }

    /* 监听好友 */
    adaptListenAllFriends();
    return 0;
}


/**
 *  功能描述: 初始化impai层参数
 *  @param 无
 *
 *  @return
 */
void initZebraEngine() {
    gCtx.zebra = zebraClient;
    gCtx.delegate = &zebarDele;

    zebraClient->init("", &zebarDele);
    qDebug() << "[imapi] << init zebra engine success";
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
    QGuiApplication app(argc, argv);
    memset(&gCtx, 0, sizeof(gCtx));
    gCtx.app = &app;

    QrCode code;


    /* 缓存 */
    createCache();

    /* 设置启动参数 */
    setAppParameter();
    initZebraEngine();


    code.setString("nanye1984");
    if (code.getQRWidth() == 0) {
        qDebug() << "create qrcode fail";
        return 0;
    }

    if (code.saveImage("./nanye.jpg", code.getQRWidth()) == false) {
        qDebug() << "save image fail";
    }



    /* 注册QML */
    registerQmlTye();

    /* 聊天主界面 */
    QQuickView viewer;
    createBaseViewer(viewer);

    /* 登录主页面 */
    QQuickView loginer;
    createLoginViewer(loginer);

    for (int i = 0 ; i < 360; i++) {
        ShadowTalkSleep(1);
        ShadowTalkSetSyncProcess(i);
    }

    /* 界面交换 */
    loginer.hide();
    viewer.show();

    ShadowTalkSleep(5);

    /* 加载XML文件 */
    if (parseEncryptXml(QString("shadowSecret"), QString("SHADOWTALK123")) < 0) {
        std::cout << "parse xml fail" << std::endl;
    }
    return app.exec();
}
