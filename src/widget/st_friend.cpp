/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称:
 *  简要描述:
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


#include "st_friend.h"
#include "st_context.h"
#include "st_log.h"
#include "st_message.h"
#include "st_utils.h"

extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 初始化一个好友
 *  @param friendIndex 好友索引
 *  @param friendName 好友名称
 *  @return 无
 */
Friend::Friend(QString friendName, int friendIndex):
    name(friendName), messageCount(0) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    newElement.insert("friendName", friendName);
    newElement.insert("friendIndex", friendIndex);

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addFriend", Q_ARG(QVariant, QVariant::fromValue(newElement)));
        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend", "add friend to widget success", friendIndex, friendName.toLatin1().data());
    } else {
        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend", "add friend to widget fail", friendIndex, friendName.toLatin1().data());
    }
}


Friend::Friend(QString friendName, int expiredTime, QString channelId,
               int session, int status, int friendIndex)
{
    name = friendName;
    defaultExpiredTime = expiredTime;
    friendChannelId = channelId;
    inSession = session;
    netStatus = status;
    messageCount = 0;
    messageUnreadCount = 0;
    id = friendIndex;

    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    QDateTime currentTime = QDateTime::currentDateTime();
    newElement.insert("friendName", friendName);
    newElement.insert("friendIndex", friendIndex);
    newElement.insert("unReadCount", 0);
    newElement.insert("messageTime", currentTime.toString("HH:mm:ss"));
    newElement.insert("netState", MessageMethodOffline);

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addFriend", Q_ARG(QVariant, QVariant::fromValue(newElement)));
        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend", "add friend to widget success", friendIndex, friendName.toLatin1().data());
    } else {
        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             "Friend", "add friend to widget fail", friendIndex, friendName.toLatin1().data());
    }
}



Friend::~Friend() {

}

/**
 *  功能描述: 将消息放入缓存列表
 *  @return 无
 */
void Friend::insertOneMessage(Message *message) {
    this->messageList.insert(this->messageList.size() + 1, *message);
    this->messageCount++;
    return;
}


/**
 *  功能描述: 存储二维码到缓存
 *  @return 无
 */
void Friend::setQrCode(QString qrCode) {
    this->qrCode = qrCode;
}

/**
 *  功能描述: 存储名字到缓存
 *  @return 无
 */
void Friend::setName(QString name) {
    this->name = name;
}

/**
 *  功能描述: SelectFriend构造函数
 *  @return 无
 */
void Friend::setNetState(int state) {
    this->netStatus = state;
}



void Friend::displayUnreadCount(int idx, int count) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "modifyUnreadCount",
                                  Q_ARG(QVariant, idx),
                                  Q_ARG(QVariant, count));
        qDebug() << "set unread count ok";
    } else {
        qDebug() << "set unread count fail";
    }
}



void Friend::setTimeAndState(int idx, int state) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {

        QDateTime currentTime = QDateTime::currentDateTime();
        QMetaObject::invokeMethod(rect, "modifyFriendTime",
                                  Q_ARG(QVariant, idx),
                                  Q_ARG(QVariant, currentTime.toString("HH:mm:ss")),
                                  Q_ARG(QVariant, state));
        qDebug() << "set time and state ok";
    } else {
        qDebug() << "set time and state fail";
    }
}




/**
 *  功能描述: SelectFriend构造函数
 *  @return 无
 */
SelectFriend::SelectFriend(QObject *parent) {

}


/**
 *  功能描述: SelectFriend的析构函数
 *  @return 无
 */
SelectFriend::~SelectFriend() {

}

/**
 *  功能描述: 改变界面上的消息列表
 *  @param index 好友索引
 *  @param name 好友名称
 *  @return 无
 */
void SelectFriend::changeMessageList(int index, QString name) {
    /* 清理界面消息 */
    clearMessageFromWidget();

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    /* 找到好友缓存 */
    Friend *f = c->getOneFriend(index);
    if (!f) {
        qDebug() << "can't find friend index - " << index;
        return;
    }

    /* 设置当前好友index */
    c->setCurrentFriendId(index);

    qDebug() << "message list size - " << f->messageList.size();

    /* 添加消息 */
    for (int i = 0; i < f->messageList.size(); i++) {
        QMap<int, Message>::iterator it = f->messageList.find(i + 1);
        if (it == f->messageList.end()) {
            return;
        }

        /* 设置显示名字 */
        QString name;
        if (it->driect == MessageDriectMe) {
            name = "Me";
        } else {
            name = f->name;
        }

        /* 添加消息到界面 */
        switch (it->messageType) {
        case MessageTypeWord:
            addMessageToWidget(f->id, name, it->messageType, it->driect, it->data);
            break;
        case MessageTypeImage:
            addImageToWidget(f->id, name, it->messageType, it->driect, it->data);
            break;
        case MessageTypeVoice:
            addVoiceToWidget(f->id, name, it->messageType, it->driect, it->data, it->voiceSeconds);
            break;
        default:
            break;
        }
    }

    displayCurrentFriendName(f->name);
    /* 界面显示清零 */
    f->displayUnreadCount(f->id - 1, 0);
    /* 未读消息计数清零 */
    f->messageUnreadCount = 0;
    return;
}



