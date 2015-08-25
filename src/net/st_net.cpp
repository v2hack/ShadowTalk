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
#include <QString>
#include <QHostInfo>
#include <QDebug>

#include <iostream>

#include "st_context.h"
#include "st_cache.h"
#include "st_net.h"
#include "st_zebra.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 获取本地ip列表
 *  @param 无
 *
 *  @return 无
 */
void getLocalIp() {
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    qDebug() << "IP Address: "<< info.addresses();
    return;
}

/**
 *  功能描述: 发送离线消息适配接口
 *  @param channelId    通道id
 *  @param messageType  消息类型
 *  @param message      消息内容
 *  @param messageId    消息索引
 *
 *  @return 无
 */
void adaptSendMessage(QString channelId, int messageType,
                      QString message, int messageId) {

    peersafe::im::Message_client *z = gCtx.zebra;
    if (z) {
        std::cout << "messageType - " << messageType << std::endl;
        std::cout << "message - " << message.toStdString() << std::endl;
        std::cout << "Epoch - " << QDateTime::currentMSecsSinceEpoch()/1000 << std::endl;
        std::cout << "message size - " << message.toStdString().size() << std::endl;

        z->send_offline_message(StringToHex(channelId.toStdString()),
                                messageType,
                                message.toStdString(),
                                60, 3600, QDateTime::currentMSecsSinceEpoch()/1000,
                                message.toStdString().size(), 0);
    }
    return;
}

/**
 *  功能描述: 坚挺好友通道适配接口
 *  @param friendChannelId  好友通道id
 *
 *  @return 无
 */
void adaptListenFriends(std::string friendChannelId) {
    int ret = 0;
    peersafe::im::Message_client *z = gCtx.zebra;
    if (!z) {
        return;
    }
    ret = z->listen_friend(friendChannelId);
    if (ret < 0) {
        std::cout << "listen friend fail" << std::endl;
    }
    return;
}

/**
 *  功能描述: 监听所有好友通道
 *  @param  无
 *
 *  @return 无
 */
void adaptListenAllFriends() {
    int ret = 0;

    Cache *c = gCtx.cache;
    peersafe::im::Message_client *z = gCtx.zebra;
    if (!z || !c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
       Friend &f = it.value();
       ret = z->listen_friend(StringToHex(f.friendChannelId.toStdString()));
       if (ret < 0) {
           std::cout << "listen friend fail" << std::endl;
           continue;
       }
    }
    std::cout << "listen all friends ok" << std::endl;
    return;
}

/**
 *  功能描述: 取消监听好友适配接口
 *  @param friendChannelId  好友通道id
 *
 *  @return 无
 */
void adaptUnistenFriends(std::string friendChannelId) {
    int ret = 0;
    peersafe::im::Message_client *z = gCtx.zebra;
    if (!z) {
        return;
    }
    ret = z->stop_listen_friend(friendChannelId);
    if (ret < 0) {
        std::cout << "unlisten friend fail" << std::endl;
    }
    return;
}
