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
void addMessageToWidget(
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

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(
            rect,
            "addMessage",
            Q_ARG(QVariant, QVariant::fromValue(data))
        );
        qDebug() << "insert one message ok";
    } else {
        qDebug() << "insert one message fail";
    }
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
void addImageToWidget(
        int uid,
        QString name,
        int type,
        int direct,
        QString messageData,
        int messageIndex)
{
    qDebug() << "receive one image";


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
void addVoiceToWidget(int uid, QString name, int type, int direct, QString voiceData, int voiceSeconds, int messageIndex)
{
    qDebug() << "receive one voice";
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

    qDebug() << "message type - " << type;

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addMessage", Q_ARG(QVariant, QVariant::fromValue(data)));
        qDebug() << "insert one voice ok";
    } else {
        qDebug() << "insert one voice fail";
    }
}


/**
 *  功能描述: clearMessageFromWidget 清理所有消息
 *  @param 无
 *
 *  @return 无
 */
void clearMessageFromWidget() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "clearMessage");
        qDebug() << "clear message ok";
    } else {
        qDebug() << "clear message fail";
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
void removeMessageByIndex(int index, int count) {
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
        qDebug() << "remove message ok";
    } else {
        qDebug() << "remove message fail";
    }
    return;
}


MessageManager::MessageManager(QObject *parent) {

}
MessageManager::~MessageManager() {

}

/**
 *  功能描述: sendMessage
 *  @param index     用户索引，这里就是0
 *  @param message   发送的消息内容，已经在QML层过滤
 *
 *  @return 无
 */
void MessageManager::sendMessage(int index, QString message) {

    /* 找到缓存 */
    Cache *c = gCtx.cache;
    QMap<int, Friend>::iterator it = c->friendList.find(c->currentUseFriendId);
    if (it == c->friendList.end()) {
        qDebug() << "can't friend firned - " << c->currentUseFriendId;
        return;
    }
    Friend *f = &(*it);
    if (!f) {
        return;
    }
    int idx = f->messageList.size() + 1;

    addMessageToWidget(0, "Me", 1, 1, message, idx);

    /* 组装缓存 */
    qDebug() << "name - " << f->name;
    Message *m = new Message;
    m->data        = message.toStdString();
    m->driect      = MessageDriectMe;
    m->messageType = MessageTypeWord;
    //m->friendIndex = c->currentUseFriendId;
    m->MessageMethord = MessageMethodOffline;

    /* 添加到缓存 */
    f->insertOneMessage(m);
    slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
         "sendMessage", "send one message", c->currentUseFriendId, message.toLatin1().data());

    /* impai 发送消息 */
    qDebug() << "message id - " << f->messageCount;
    adaptSendMessage(f->friendChannelId, 1, message, f->messageCount);
    return;
}

