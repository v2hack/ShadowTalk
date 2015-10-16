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
 *  @param friendName   好友名字
 *  @param friendIndex  好友索引
 *
 *  @return 无
 */
void addFrientToChat(QString friendName, QString shortName, int friendIndex, int listViewIndex)
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
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "insertFriend",
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
}

/**
 *  功能描述: 从chatlist界面删除好友
 *  @param friendName   好友名字
 *  @param friendIndex  好友索引
 *
 *  @return 无
 */
void removeFrientFromChat(int chatIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "removeFriend",
                    Q_ARG(QVariant, chatIndex));
        if (ret == false) {
            qDebug() << "invokeMethod (removeFriend) fail";
        }
    }
}


void updateListIndexForChat(int index, int listViewIndex) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "updateListIndex",
                    Q_ARG(QVariant, index),
                    Q_ARG(QVariant, listViewIndex));
        if (ret == false) {
            qDebug() << "invokeMethod (updateListIndex) fail";
        }
    }
}



/**
 *  功能描述: 从chatlist界面删除好友
 *  @param friendName   好友名字
 *  @param friendIndex  好友索引
 *
 *  @return 无
 */
void displayChatNetState(int idx, int state) {
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    int chatIdx = 0, flag = 0;
    QList<ChatItem *>::iterator it;
    for (it = c->chatList.begin(); it != c->chatList.end(); it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == idx) {
                flag = 1;
                break;
            }
            chatIdx++;
        }
    }
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
        QMetaObject::invokeMethod(
                    rect,
                    "modifyFriendTime",
                    Q_ARG(QVariant, chatIdx),
                    Q_ARG(QVariant, currentTime.toString("HH:mm:ss")),
                    Q_ARG(QVariant, state)
                    );
        qDebug() << "set time and state ok";
    } else {
        qDebug() << "set time and state fail";
    }
}


void displayChatUnreadCount(int idx, int count) {

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    int chatIdx = 0, flag = 0;
    QList<ChatItem *>::iterator it;
    for (it = c->chatList.begin(); it != c->chatList.end(); it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == idx) {
                flag = 1;
                break;
            }
            chatIdx++;
        }
    }
    if (flag == 0) {
        return;
    }

    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "modifyUnreadCount",
                    Q_ARG(QVariant, chatIdx),
                    Q_ARG(QVariant, count)
                    );
    } else {
        qDebug() << "set unread count fail";
    }
}


void refreshChatListPosition(int cacheIndex, int itemType) {
    QString name;
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    switch (itemType) {
    case CHATITEM_TYPE_FRIEND:
    {
        Friend *f = c->getOneFriend(cacheIndex);
        if (f) {
            name = f->name;
        }
        break;
    }
    case CHATITEM_TYPE_GROUP:
    {
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
        qDebug() << "[c++] : refresh chat list position - get name fail";
        return;
    }

    int ret = c->atFirstPosition(cacheIndex, itemType);
    /* 需要交换位置 */
    if (ret == -2) {
        qDebug() << "[c++] : chatlist - change position";
        c->removeOneChat(cacheIndex, itemType);
        c->insertOneChat(cacheIndex, itemType, name);
    }
    /* 需要插入新成员 */
    if (ret == -1) {
        qDebug() << "[c++] : chatlist - insert new one";
        c->insertOneChat(cacheIndex, itemType, name);
    }
    return;
}


