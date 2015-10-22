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
#include "st_chat.h"

extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 初始化一个好友
 *  @param friendIndex 好友索引
 *  @param friendName 好友名称
 *  @return 无
 */
Friend::Friend(QString friendName, int friendIndex):
    name(friendName), messageCount(0)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    newElement.insert("friendName", friendName);
    newElement.insert("friendIndex", friendIndex);

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "addFriend",
                    Q_ARG(QVariant, QVariant::fromValue(newElement))
                    );
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
}

/**
 *  功能描述: 好友构造函数，初始化一个好友
 *  @param friendName   好友名字
 *  @param expiredTime  过期时间
 *  @param channelId    通道id
 *  @param session      是否在临时列表中
 *  @param status       在线状态
 *  @param friendIndex  好友索引
 *
 *  @return 无
 */
Friend::Friend(QString friendName, int expiredTime, QString channelId,
               int session, int status, int friendIndex)
{
    cacheIndex = friendIndex;
    messageCount = 0;
    name = friendName;
    inSession = session;
    netStatus = status;
    messageUnreadCount = 0;
    friendChannelId    = channelId;
    defaultExpiredTime = expiredTime;
    firstLetter = QString("");

    QVariant tempLetter;

    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "firstLetter",
                    Qt::DirectConnection,
                    Q_RETURN_ARG(QVariant, tempLetter),
                    Q_ARG(QVariant, friendName));
        if (ret == false) {
            qDebug() << "invokeMethod (firstLetter) fail";
        }

        firstLetter = tempLetter.toString();
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
}

/**
 *  功能描述: 好友析构函数
 *  @param  无
 *
 *  @return 无
 */
Friend::~Friend() {}

/**
 *  功能描述: 将消息放入缓存列表
 *  @param message 消息结构
 *
 *  @return 无
 */
void Friend::insertOneMessage(Message *message)
{
    this->messageList.insert(this->messageList.size(), *message);
    this->messageCount++;
    return;
}


/**
 *  功能描述: 存储二维码到缓存
 *  @param qrCode 二维码串
 *
 *  @return 无
 */
void Friend::setQrCode(QString qrCode)
{
    this->qrCode = qrCode;
    return;
}

/**
 *  功能描述: 存储名字到缓存
 *  @param name 用户名设置
 *
 *  @return 无
 */
void Friend::setName(QString name)
{
    this->name = name;
    return;
}

/**
 *  功能描述: 设置用户网络状态
 *  @param state 网络状态值
 *
 *  @return 无
 */
void Friend::setNetState(int state)
{
    this->netStatus = state;
    return;
}

/**
 *  功能描述: 调用qml对象，设置好友界面未读消息数量
 *  @param idx    好友索引
 *  @param count  未读消息数量
 *
 *  @return 无
 */
void Friend::displayUnreadCount(int idx, int count)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "modifyUnreadCount",
                    Q_ARG(QVariant, idx),
                    Q_ARG(QVariant, count)
                    );
        qDebug() << "set unread count ok";
    } else {
        qDebug() << "set unread count fail";
    }
    return;
}

/**
 *  功能描述: 调用qml对象，设置好友界面未读消息数量
 *  @param idx    好友索引
 *  @param count  未读消息数量
 *
 *  @return 无
 */
void Friend::setTimeAndState(int idx, int state)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QDateTime currentTime = QDateTime::currentDateTime();
        QMetaObject::invokeMethod(
                    rect,
                    "modifyFriendTime",
                    Q_ARG(QVariant, idx),
                    Q_ARG(QVariant, currentTime.toString("HH:mm:ss")),
                    Q_ARG(QVariant, state)
                    );
        qDebug() << "set time and state ok";
    } else {
        qDebug() << "set time and state fail";
    }
    return;
}


/**
 *  功能描述: 设置friendlistView中的item背景色为透明
 *
 *  @return 无
 */
void Friend::setFriendlistBackGroundColor(int colorFlag)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "modifyBackColor",
              Q_ARG(QVariant, listViewIndex), Q_ARG(QVariant, colorFlag));
    }
    return;
}

/**
 *  功能描述: 设置chatlistView中的item背景色为透明
 *
 *  @return 无
 */
void Friend::setChatlistBackGroundColor(int colorFlag, int chatListIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "modifyBackColor",
             Q_ARG(QVariant, chatListIndex), Q_ARG(QVariant, colorFlag));
    }
    return;
}

/**
 *  功能描述: SelectFriend构造函数
 *  @return 无
 */
SelectFriend::SelectFriend(QObject *parent)
{
	parent = parent;
    return;
}

/**
 *  功能描述: SelectFriend的析构函数
 *  @return 无
 */
SelectFriend::~SelectFriend() {}


void SelectFriend::refreshFriendMessage(Friend *f)
{
    /* 添加消息 */
    for (int i = 0; i < f->messageList.size(); i++) {
        int idx = i;
        QMap<int, Message>::iterator it = f->messageList.find(i);
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
            MessageWidget::addMessageToWidget(f->cacheIndex, name, it->messageType,
                               it->driect, QString::fromStdString(it->data), idx);
            break;
        case MessageTypeImage:
            MessageWidget::addImageToWidget(f->cacheIndex, name, it->messageType,
                             it->driect, it->data, idx);
            break;
        case MessageTypeVoice:
            MessageWidget::addVoiceToWidget(f->cacheIndex, name, it->messageType, it->driect,
                             QString::fromStdString(it->data), it->voiceSeconds, idx);
            break;
        default:
            break;
        }
    }
    return;
}

void SelectFriend::refreshFriendStatistics(Friend *f)
{
    /* 界面显示清零 */
    Utils::displayCurrentFriendName(f->name);
    /* 未读消息计数清零 */
    Chat::displayChatUnreadCount(f->cacheIndex, 0, CHATITEM_TYPE_FRIEND);
    f->messageUnreadCount = 0;
    return;
}


/**
 *  功能描述: 改变界面上的消息列表
 *  @param index 好友索引
 *  @param name 好友名称
 *  @return 无
 */
void SelectFriend::changeMessageListForFlist(int friendCacheIndex, QString name)
{
    qDebug() << "c++: friend changeMessageListForFlist index - " << friendCacheIndex;

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    /* 找到好友缓存 */
	Friend *f = c->getOneFriend(friendCacheIndex);
    if (!f) {
        qDebug() << "c++: get friend fail by index - " << friendCacheIndex;
        return;
    }

    if (c->currentUseId_ != friendCacheIndex || c->currentUseType_ != CHATITEM_TYPE_FRIEND) {
        MessageWidget::clearMessageFromWidget();
        this->refreshFriendMessage(f);
    }

    this->refreshFriendStatistics(f);
    Utils::clearCurrentItemHighLight(c);
    c->setCurrentId(friendCacheIndex, CHATITEM_TYPE_FRIEND, name);
    Utils::setFriendItemHighLight(c, f, friendCacheIndex);
    qDebug() << "\n";
    return;
}

/**
 *  功能描述: 改变界面上的消息列表
 *  @param index 好友索引
 *  @param name 好友名称
 *  @return 无
 */
void SelectFriend::changeMessageListForClist(int friendCacheIndex, QString name)
{
    qDebug() << "c++: friend changeMessageListForClist index - " << friendCacheIndex;

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    /* 找到好友缓存 */
	Friend *f = c->getOneFriend(friendCacheIndex);
    if (!f) {
        qDebug() << "c++: get friend fail by index - " << friendCacheIndex;
        return;
    }

    if (c->currentUseId_ != friendCacheIndex || c->currentUseType_ != CHATITEM_TYPE_FRIEND) {
        MessageWidget::clearMessageFromWidget();
        this->refreshFriendMessage(f);
    }

    this->refreshFriendStatistics(f);
    Utils::clearCurrentItemHighLight(c);
    c->setCurrentId(friendCacheIndex, CHATITEM_TYPE_FRIEND, name);
    Utils::setFriendItemHighLight(c, f, friendCacheIndex);
    qDebug() << "\n";
    return;
}

