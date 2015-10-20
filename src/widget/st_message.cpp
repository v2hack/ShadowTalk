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
#include <QString>
#include <stdio.h>
#include <stdlib.h>

#include "st_friend.h"
#include "st_context.h"
#include "st_message.h"
#include "st_log.h"
#include "st_net.h"
#include "st_picture.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: addMessageToWidget 添加消息到界面
 *  @param uid          用户索引
 *  @param name         用户名
 *  @param type         消息类型: 文字、声音、图片
 *  @param direct       消息的方向
 *  @param messageData  数据内容
 *  @param messageIndex 消息索引
 *
 *  @return 无
 */
void MessageWidget::addMessageToWidget(
        int uid,
        QString name,
        int type,
        int direct,
        QString messageData,
        int messageIndex)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap data;
    data.insert("uid", uid);
    data.insert("name", name);
    data.insert("dataType", type);
    data.insert("direct", direct);
    data.insert("userMessage", messageData);
    data.insert("voiceSeconds", 0);
    data.insert("messageIndex", messageIndex);
    data.insert("userPicture", "");
    data.insert("pictureHeight", "");
    data.insert("pictureWidth", "");

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "addMessage",
                    Q_ARG(QVariant, QVariant::fromValue(data))
                    );
        qDebug() << "[c++] : insert one message ok";
    } else {
        qDebug() << "[c++] : insert one message fail";
    }

    qDebug() << "[c++] : addMessageToWidget - fid:" <<  uid << " mid:"<< messageIndex;
}

/**
 *  功能描述: addImageToWidget 添加图片消息到界面
 *  @param uid          用户索引
 *  @param name         用户名
 *  @param type         消息类型: 文字、声音、图片
 *  @param direct       消息的方向
 *  @param messageData  数据内容
 *  @param messageIndex 消息索引
 *
 *  @return 无
 */
void MessageWidget::addImageToWidget(
        int uid,
        QString name,
        int type,
        int direct,
        std::string messageData,
        int messageIndex)
{
    qDebug() << "[c++] : receive one image";

    int height = 0, width = 0;
    /* 持久化图片文件 */
    QUrl picturePath = NormalPicture::displayPicture(
                QString::number(uid),
                QString::number(messageIndex),
                messageData);
    if (picturePath.isEmpty()) {
        return;
    }

    /* 图片缩放 */
    if (NormalPicture::shrinkPicture(picturePath.toLocalFile(), height, width, 300) < 0) {
        return;
    }

    /* 添加qml对象属性 */
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap data;
    data.insert("uid", uid);
    data.insert("name", name);
    data.insert("dataType", type);
    data.insert("direct", direct);
    data.insert("userMessage", 0);
    data.insert("voiceSeconds", 0);
    data.insert("messageIndex", messageIndex);
    data.insert("userPicture", picturePath.toString());
    data.insert("pictureHeight", height);
    data.insert("pictureWidth", width);

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addMessage", Q_ARG(QVariant, QVariant::fromValue(data)));
        qDebug() << "[c++] : insert one voice ok";
    } else {
        qDebug() << "[c++] : insert one voice fail";
    }
    qDebug() << "[c++] : addImageToWidget - fid:" <<  uid << " mid:"<< messageIndex;
}

/**
 *  功能描述: 添加声音到qml界面
 *  @param uid           用户id
 *  @param name          名字
 *  @param type          控件类型
 *  @param direct        消息方向
 *  @param voiceData     声音数据
 *  @param voiceSeconds  声音秒数
 *  @param messageIndex  消息索引
 *
 *  @return 无
 */
void MessageWidget::addVoiceToWidget(int uid, QString name, int type,
       int direct, QString voiceData, int voiceSeconds, int messageIndex)
{
    qDebug() << "[c++] : receive one voice";
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap data;
    data.insert("uid", uid);
    data.insert("name", name);
    data.insert("dataType", type);
    data.insert("direct", direct);
    data.insert("userMessage", voiceData);
    data.insert("voiceSeconds", voiceSeconds);
    data.insert("messageIndex", messageIndex);
    data.insert("userPicture", "");
    data.insert("pictureHeight", "");
    data.insert("pictureWidth", "");

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addMessage", Q_ARG(QVariant, QVariant::fromValue(data)));
        qDebug() << "[c++] : insert one voice ok";
    } else {
        qDebug() << "[c++] : insert one voice fail";
    }
    qDebug() << "[c++] :  addVoiceToWidget - fid:" <<  uid << " mid:"<< messageIndex;
}


/**
 *  功能描述: clearMessageFromWidget 清理所有消息
 *  @param 无
 *
 *  @return 无
 */
void MessageWidget::clearMessageFromWidget()
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "clearMessage");
        qDebug() << "[c++] : clear message ok";
    } else {
        qDebug() << "[c++] : clear message fail";
    }
    return;
}

/**
 *  功能描述: 清理界面上的所有好友
 *  @param 无
 *
 *  @return 无
 */
void MessageWidget::clearFriendFromWidget()
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "clearFriend");
        qDebug() << "[c++] : clear friend ok";
    } else {
        qDebug() << "[c++] : clear friend fail";
    }
    return;
}


/**
 *  功能描述: removeMessageByIndex
 *  @param index     消息索引
 *  @param message   在index基础上删除消息的数量
 *
 *  @return 无
 */
void MessageWidget::removeMessageByIndex(int index, int count)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap data;
    data.insert("index", index);
    data.insert("count", count);

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "removeMessage", Q_ARG(QVariant, QVariant::fromValue(data)));
        qDebug() << "[c++] : remove message ok";
    } else {
        qDebug() << "[c++] : remove message fail";
    }
    return;
}


MessageManager::MessageManager(QObject *parent) {
    parent = parent;
}
MessageManager::~MessageManager() {

}


void MessageManager::sendGroupMessage(QString &message) {
    Cache *c = gCtx.cache;
    Group *g = c->getOneGroup(c->currentUseId_);
    if (!g) {
        qDebug() << "[c++] : can't current group idx - " << c->currentUseId_;
        return;
    }

    qDebug() << "[c++] : message - " << message;

    // TODO 将消息加入缓存

    // TODO 转发给手机端

    Chat::refreshChatListPosition(g->gid_, CHATITEM_TYPE_GROUP);
    return;
}

void MessageManager::sendFriendMessage(QString &message) {
    Cache *c = gCtx.cache;

    Friend *f = c->getOneFriend(c->currentUseId_);
    if (!f) {
        qDebug() << "[c++] : can't current friend idx - " << c->currentUseId_;
        return;
    }
    qDebug() << "[c++] : message - " << message;

    int idx = f->messageList.size() + 1;

    MessageWidget::addMessageToWidget(0, "Me", 1, 1, message, idx);

    /* 组装缓存 */
    Message *m     = new Message;
    m->data        = message.toStdString();
    m->driect      = MessageDriectMe;
    m->messageType = MessageTypeWord;
    m->MessageMethord = MessageMethodOffline;

    /* 添加到缓存 */
    f->insertOneMessage(m);
    slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
         "sendMessage", "send one message", c->currentUseId_, message.toLatin1().data());

    /* impai 发送消息 */
    Adapt::adaptSendMessage(f->friendChannelId, 1, message);

    Chat::refreshChatListPosition(f->cacheIndex, CHATITEM_TYPE_FRIEND);
    return;
}


/**
 *  功能描述: sendMessage
 *  @param index     用户索引，这里就是0
 *  @param message   发送的消息内容，已经在QML层过滤
 *
 *  @return 无
 */
void MessageManager::sendMessage(QString message) {

    /* 找到缓存 */
    Cache *c = gCtx.cache;
    if (c->currentUseType_ == CHATITEM_TYPE_FRIEND) {
        qDebug() << "[c++] : send one friend message - " << c->currentUseId_;
        this->sendFriendMessage(message);
    } else {
        qDebug() << "[c++] : send one group message - " << c->currentUseId_;
        this->sendGroupMessage(message);
    }
    return;
}

