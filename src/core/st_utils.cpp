/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_utils.cpp
 *  简要描述:
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <QTime>
#include <QObject>
#include <QWidget>
#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "st_context.h"
#include "st_cache.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 休眠函数
 *  @param msec 毫秒
 *
 *  @return 无
 */
void ShadowTalkSleep(unsigned int msec) {
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

/**
 *  功能描述: 播放接收消息声音
 *  @param  无
 *
 *  @return 无
 */
void playMessageSound() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("MessageSound");
    if (rect) {
        QMetaObject::invokeMethod(rect, "playMessageSound");
    }
}

/**
 *  功能描述: 设置界面上当前还有的名字
 *  @param  currentFriendName 当前好友名
 *
 *  @return 无
 */
void displayCurrentFriendName(QString currentFriendName)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("DispalyCurrentFriendName");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setCurrentFriendName",  Q_ARG(QVariant, currentFriendName));
    } else {
        qDebug() << "can't find object DispalyCurrentFriendName";

    }
}
