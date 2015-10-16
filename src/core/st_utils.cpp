﻿/*******************************************************************
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
#include <QString>

#include "st_context.h"
#include "st_cache.h"
#include "st_utils.h"
#include "st_parsexml.h"
#include "st_log.h"
#include "st_utils.h"
#include "st_net.h"
#include "st_login.h"
#include "st_chat.h"

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


void stopMessageVoice() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("MessageVoice");
    if (rect) {
        QMetaObject::invokeMethod(rect, "stopMessageVoice");
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
    for(int i = 0; i < 360; i++) {
        ShadowTalkSetSyncProcessClean(i);
    }
    gCtx.changeFlag = 1; /* 通知线程切换窗口 */
    gCtx.windowFlag = 1; /* 当前应该显示主窗口 */
    setReceiveEnable(true);
}

/**
 *  功能描述: 联系人页面，按照首字符显示好友
 *  @param  无
 *
 *  @return
 */
void walkCacheAddFriendAndGroup() {
    char firstLetter[27] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                            'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                            'W', 'X', 'Y', 'Z', '#'};
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    int listViewIndex = 0;

    QMap<int, Group>::iterator it;
    for(it = c->groupList.begin(); it != c->groupList.end(); it++) {
        Group &g = it.value();
        qDebug() << "[c++] : add group - " << g.gourpName_;
        addGroupIntoWidget(g.gourpName_, it.key(), listViewIndex);
        g.listViewIndex = listViewIndex;
        listViewIndex++;
    }

    for (int i = 0; i < 27; i++) {
        QMap<int, Friend>::iterator it;
        for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
            Friend &f = it.value();
            if (f.loadStatus == 1) {
                continue;
            }
            if (f.firstLetter.toLatin1().data()[0] == firstLetter[i]) {
                qDebug() << "[c++] : add friend - " << f.name;
                addFriendIntoWidget(f.name, it.key(), listViewIndex);
                f.listViewIndex = listViewIndex;
                listViewIndex++;
                f.loadStatus = 1;
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
void addFriendIntoWidget(QString friendName, int friendIndex, int listViewIndex)
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
    newElement.insert("listViewIndex", listViewIndex);
    newElement.insert("backGroundColor", 0);

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

/**
 *  功能描述: 将缓存中的组添加到界面
 *  @param  groupName   组名字
 *  @param  groupIndex  组索引
 *
 *  @return
 */
void addGroupIntoWidget(QString groupName, int groupIndex, int listViewIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    QDateTime currentTime = QDateTime::currentDateTime();
    newElement.insert("friendName",  groupName);
    newElement.insert("friendIndex", groupIndex);
    newElement.insert("unReadCount", 0);
    newElement.insert("messageTime", currentTime.toString("HH:mm:ss"));
    newElement.insert("netState",    MessageMethodOffline);
    newElement.insert("shortName",   "Group");
    newElement.insert("listViewIndex", listViewIndex);
    newElement.insert("backGroundColor", 0);

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "addGroup",
                    Q_ARG(QVariant, QVariant::fromValue(newElement)));

        slog("func<%s> : msg<%s> para<groupName - %d, groupIndex - %s>\n",
             "Group",
             "add group to widget success",
             groupIndex,
             groupName.toLatin1().data());
    } else {

        slog("func<%s> : msg<%s> para<groupName - %d, groupIndex - %s>\n",
             "Group",
             "add group to widget fail",
             groupIndex,
             groupName.toLatin1().data());
    }
    return;
}



void clearCurrentItemHighLight(Cache *cache) {

    int chatListSeq = 0;
    /* 取消当前好友的背景高亮 */
    if (cache->currentUseType == CHATITEM_TYPE_FRIEND) {
		Friend *friend_ = cache->getOneFriend(cache->currentUseId);
        if (friend_) {
            friend_->setFriendlistBackGroundColor(0);
            chatListSeq = cache->getPositionNum(cache->currentUseId, CHATITEM_TYPE_FRIEND);
            if (chatListSeq >= 0) {
                friend_->setChatlistBackGroundColor(0, chatListSeq);
            }
        } else {
            qDebug() << "[c++] : can't friend - " << cache->currentUseId;
        }

    /* 取消当前组的背景高亮 */
    } else {
        Group *group = cache->getOneGroup(cache->currentUseId);
        if (group) {
            group->setFriendlistBackGroundColor(0);
            chatListSeq = cache->getPositionNum(cache->currentUseId, CHATITEM_TYPE_GROUP);
            if (chatListSeq >= 0) {
                group->setChatlistBackGroundColor(0, chatListSeq);
            }
        } else {
            qDebug() << "[c++] : can't group - " << cache->currentUseId;
        }
    }
}


void setGroupItemHighLight(Cache *cache,  Group *group, int groupCacheindex) {

    /* 在chat listView中高亮 */
    int chatListSeq = cache->getPositionNum(groupCacheindex, CHATITEM_TYPE_GROUP);
    if (chatListSeq >= 0) {
        group->setChatlistBackGroundColor(1, chatListSeq);
    }
    /* 在friend listView中高亮 */
    group->setFriendlistBackGroundColor(1);

    /* 设置新的当前好友item */
    cache->setCurrentId(groupCacheindex, CHATITEM_TYPE_GROUP, group->gourpName_);
    return;
}

void setFriendItemHighLight(Cache *cache,  Friend *friend_, int friendCacheIndex) {
    /* 在chat listView中高亮 */
    int chatListSeq = cache->getPositionNum(friendCacheIndex, CHATITEM_TYPE_FRIEND);
    if (chatListSeq >= 0) {
        friend_->setChatlistBackGroundColor(1, chatListSeq);
    }
    /* 在friend listView中高亮 */
    friend_->setFriendlistBackGroundColor(1);

    /* 设置新的当前好友item */
    cache->setCurrentId(friendCacheIndex, CHATITEM_TYPE_FRIEND, friend_->name);
    return;
}


/**
 *  功能描述: SelectFriend构造函数
 *  @return 无
 */
WindowClose::WindowClose(QObject *parent) { parent = parent; }

/**
 *  功能描述: SelectFriend的析构函数
 *  @return 无
 */
WindowClose::~WindowClose() {}

/**
 *  功能描述: 发送给手机端下线消息，并退出程序
 *  @return 无
 */
void WindowClose::closeWindowProcess() {

    QQuickView *v = gCtx.viewer;
    QQuickView *l = gCtx.viewer;

    if (v) {
        v->close();
        l->close();
    }

    peersafe::im::Message_client *z = gCtx.zebra;
    if (z) {
        z->send_offline_message(gCtx.phoneSyncChannel, ImapiMessageType_PCOffLine,
                                "PC exit", 60, 3600, QDateTime::currentMSecsSinceEpoch()/1000, 7, 0);
    }
    gCtx.threadStop = 1;
    ShadowTalkSleep(3000);
    exit(0);
}

