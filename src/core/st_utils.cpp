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

#include <iostream>
#include <fstream>

#include "st_context.h"
#include "st_cache.h"
#include "st_utils.h"
#include "st_parsexml.h"
#include "st_log.h"
#include "st_utils.h"
#include "st_net.h"

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
 *  功能描述: 访问qml对象，播放音频文件
 *  @param voiceFilePath 音频文件路径
 *
 *  @return 无
 */
void playMessageVoice(QString voiceFilePath) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("MessageVoice");
    if (rect) {
        QMetaObject::invokeMethod(rect, "playMessageVoice",  Q_ARG(QVariant, voiceFilePath));
    }
}

/**
 *  功能描述: 设置界面上当前还有的名字
 *  @param  currentFriendName 当前好友名
 *
 *  @return 无
 */
void displayCurrentFriendName(QString currentFriendName) {
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
    return;
}


void writeXmlFile(std::string fileName, std::string data) {
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::binary);
    file.write(data.c_str(), data.size());
    file.close();
    return;
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
    sDecryptData = gCtx.zebra->decrypt(sEncryptData, sPasswd);
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
 *  功能描述: 设置主页面可见
 *  @param  无
 *
 *  @return
 */
void setMainWindowVisible() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }
    QObject *rect = rootObject->findChild<QObject*>("RootBaseWindow");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setBaseWindowVisible");
    }
}


/**
 *  功能描述: 设置主页面不可见
 *  @param  无
 *
 *  @return
 */
void setMainWindowUnvisible() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }
    QObject *rect = rootObject->findChild<QObject*>("RootBaseWindow");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setBaseWindowUnvisible");
    }
}


/**
 *  功能描述: 设置登录界面可见
 *  @param  无
 *
 *  @return
 */
void setLoginWindowVisible() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }
    QObject *rect = rootObject->findChild<QObject*>("RootLoginWindow");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setLoginWindowVisible");
    }
}

/**
 *  功能描述: 设置登录界面不可见
 *  @param  无
 *
 *  @return
 */
void setLoginWindowUnvisible() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }
    QObject *rect = rootObject->findChild<QObject*>("RootLoginWindow");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setLoginWindowUnvisible");
    }
}

/**
 *  功能描述: 界面切换，设置base页面隐藏
 *  @param  无
 *
 *  @return
 */
void displayBaseView() {
    gCtx.loginer->hide();
    gCtx.viewer->show();
}

/**
 *  功能描述: 界面切换，设置登录页面隐藏
 *  @param  无
 *
 *  @return
 */
void displayLoginView() {
    gCtx.viewer->hide();
    gCtx.loginer->show();
}

/**
 *  功能描述: 联系人页面，按照首字符显示好友
 *  @param  无
 *
 *  @return
 */
void walkCacheAddFriend() {
    char firstLetter[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                            'W', 'X', 'Y', 'Z', '#'};
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    int idx = 0;
    for (int i = 0; i < 27; i++) {
        QMap<int, Friend>::iterator it;
        for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
            Friend &f = it.value();
            if (f.firstLetter.toLatin1().data()[0] == firstLetter[i]) {
                qDebug() << "add friend - " << f.name;
                addFriendIntoWidget(f.name, idx);
                f.id = idx;
                idx++;
            } else {
                continue;
            }
        }
    }
}

/**
 *  功能描述: 将缓存中的好友添加到界面
 *  @param  friendName   好友名字
 *  @param  friendIndex  好友索引
 *
 *  @return
 */
void addFriendIntoWidget(QString friendName, int friendIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    QDateTime currentTime = QDateTime::currentDateTime();
    newElement.insert("friendName",  friendName);
    newElement.insert("friendIndex", friendIndex);
    newElement.insert("unReadCount", 0);
    newElement.insert("messageTime", currentTime.toString("HH:mm:ss"));
    newElement.insert("netState",    MessageMethodOffline);
    newElement.insert("shortName",   "");

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "addFriend",
                    Q_ARG(QVariant, QVariant::fromValue(newElement)));

        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend",
             "add friend to widget success",
             friendIndex,
             friendName.toLatin1().data());
    } else {

        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend",
             "add friend to widget fail",
             friendIndex,
             friendName.toLatin1().data());
    }
    return;
}
