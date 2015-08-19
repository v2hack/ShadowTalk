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

void getLocalIp() {
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    qDebug() << "IP Address: "<< info.addresses();
    return;
}


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
