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

#include "pixelsize.h"
#include "friend.h"
#include "cache.h"
#include "context.h"
#include "utils.h"
#include "login.h"

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
    qmlRegisterType<PointSizeToPixelSize>(
                "st.font.PointSizeToPixelSize",
                1, 0, "PointSizeToPixelSize");
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

    /* 注册QML */
    registerQmlTye();

    QQuickView viewer;
    createBaseViewer(viewer);

    QQuickView loginer;
    createLoginViewer(loginer);

    /* 缓存 */
    createCache();

    for (int i = 0 ; i < 360; i++) {
        ShadowTalkSleep(4);
        ShadowTalkSetSyncProcess(i);
    }

    return app.exec();
}
