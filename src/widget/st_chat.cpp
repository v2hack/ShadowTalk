/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_chat.cpp
 *  简要描述: 主要负责程序聊天列表页面的处理
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include <QWidget>
#include <QtQuick/QQuickView>
#include <QDateTime>
#include <stdio.h>
#include <stdlib.h>
#include "st_chat.h"
#include "st_friend.h"
#include "st_context.h"
#include "st_log.h"
#include "st_message.h"
#include "st_utils.h"
#include "st_cache.h"

extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 加好友到chatList页面
 *  @param friendName     好友名字
 *  @param shortName      好友索引
 *  @param friendIndex    短名， 这里是Group后者Friend
 *  @param listViewIndex  在listview中的索引
 *
 *  @return 无
 */
void Chat::addFrientToChat(QString friendName, QString shortName,
      int friendIndex, int listViewIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    newElement.insert("friendName",  friendName);
    newElement.insert("friendIndex", friendIndex);
    newElement.insert("shortName",   shortName);
    newElement.insert("friendIndex", friendIndex);
    newElement.insert("unReadCount", 0);
    newElement.insert("netState",    MessageMethodOffline);
    newElement.insert("listViewIndex", listViewIndex);
    newElement.insert("backGroundColor", 0);

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "insertFriend",
                    Q_ARG(QVariant, QVariant::fromValue(newElement)));
        if (ret == false) {
            qDebug() << "invokeMethod (addFriend) fail";
        }

        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend",
             "add friend to chat widget success",
             friendIndex,
             friendName.toLatin1().data());

    } else {

        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend",
             "add friend to chat widget fail",
             friendIndex,
             friendName.toLatin1().data());
    }
    return;
}

/**
 *  功能描述: 从chatlist界面删除好友
 *  @param chatIndex   chat缓存中的索引
 *
 *  @return 无
 */
void Chat::removeFrientFromChat(int chatIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "removeFriend", Q_ARG(QVariant, chatIndex));
        if (ret == false) {
            qDebug() << "c++: invokeMethod (removeFriend) fail";
        }
    }
    return;
}

/**
 *  功能描述: 更新qml中listiew中的索引
 *  @param index          chat缓存中的索引
 *  @param listViewIndex  listViewIndex中的索引
 *
 *  @return 无
 */
void Chat::updateListIndexForChat(int index, int listViewIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "updateListIndex",
                    Q_ARG(QVariant, index), Q_ARG(QVariant, listViewIndex));
        if (ret == false) {
            qDebug() << "c++: invokeMethod (updateListIndex) fail";
        }
    }
    return;
}


/**
 *  功能描述: 从chatlist界面删除好友
 *  @param idx    好友索引
 *  @param state  在线或者离线
 *
 *  @return 无
 */
void Chat::displayChatNetState(int idx, int state)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    int chatIdx = 0, flag = 0;
    c->chatMutex_.lock();
    QList<ChatItem *>::iterator it;
    for (it = c->chatList_.begin(); it != c->chatList_.end(); it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == idx) {
                flag = 1;
                break;
            }
            chatIdx++;
        }
    }
    c->chatMutex_.unlock();
    if (flag == 0) {
        return;
    }

    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        QDateTime currentTime = QDateTime::currentDateTime();
        QMetaObject::invokeMethod(rect, "modifyFriendTime", Q_ARG(QVariant, chatIdx),
                    Q_ARG(QVariant, currentTime.toString("HH:mm:ss")),
                    Q_ARG(QVariant, state));
    }
    return;
}

/**
 *  功能描述: 设置chat listview中的未读消息数量
 *  @param idx    好友索引
 *  @param count  未读消息数量
 *
 *  @return 无
 */
void Chat::displayChatUnreadCount(int idx, int count, int type)
{
    int chatIdx = 0, flag = 0;

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    c->chatMutex_.lock();
    QList<ChatItem *>::iterator it;
    for (it = c->chatList_.begin(); it != c->chatList_.end(); it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == idx && item->type == type) {
                flag = 1;
                break;
            }
            chatIdx++;
        }
    }
    c->chatMutex_.unlock();
    if (flag == 0) {
        return;
    }
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "modifyUnreadCount",
                    Q_ARG(QVariant, chatIdx), Q_ARG(QVariant, count));
    }
    return;
}

/**
 *  功能描述: 更新chat listview中的位置
 *  @param cacheIndex  好友索引
 *  @param itemType    类型:组还是好友
 *
 *  @return 无
 */
void Chat::refreshChatListPosition(int cacheIndex, int itemType)
{
    QString name;
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    switch (itemType) {
    case CHATITEM_TYPE_FRIEND: {
        Friend *f = c->getOneFriend(cacheIndex);
        if (f) {
            name = f->name;
        }
        break;
    }
    case CHATITEM_TYPE_GROUP: {
        Group *g = c->getOneGroup(cacheIndex);
        if (g) {
            name = g->gourpName_;
        }
        break;
    }
    default:
        return;
    }

    if (name.isEmpty()) {
        qDebug() << "c++: refresh chat list position - get name fail";
        return;
    }

    int ret = c->atFirstPosition(cacheIndex, itemType);
    /* 需要交换位置 */
    if (ret == -2) {
        qDebug() << "c++: chatlist - change position";
        c->removeOneChat(cacheIndex, itemType);
        c->insertOneChat(cacheIndex, itemType, name);
    }
    /* 需要插入新成员 */
    if (ret == -1) {
        qDebug() << "c++: chatlist - insert new one";
        c->insertOneChat(cacheIndex, itemType, name);
    }
    return;
}
