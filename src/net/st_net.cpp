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
#include "st_utils.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 获取本地ip列表
 *  @param 无
 *
 *  @return 无
 */
void Adapt::adaptGetLocalIp()
{
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
void Adapt::adaptSendMessage(QString channelId, int messageType, QString message)
{
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (z) {
        z->send_offline_message(StringToHex(channelId.toStdString()), messageType, message.toStdString(),
               60, 3600, QDateTime::currentMSecsSinceEpoch()/1000, message.toStdString().size(), 0);
        z->send_sync_message(gCtx.phoneSyncChannel, StringToHex(channelId.toStdString()), messageType + 2000,
               message.toStdString(), 60, 3600, QDateTime::currentMSecsSinceEpoch()/1000,
               message.toStdString().size(), 0);
        qDebug() << "c++: adaptSendMessage - send sync message";
    }
    return;
}

/**
 *  功能描述: 坚挺好友通道适配接口
 *  @param friendChannelId  好友通道id
 *
 *  @return 无
 */
void Adapt::adaptListenFriends(std::string friendChannelId)
{
    int ret = 0;
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (!z) {
        return;
    }
    ret = z->listen_friend(friendChannelId);
    if (ret < 0) {
        std::cout << "c++: listen friend fail" << std::endl;
    }
    return;
}

/**
 *  功能描述: 监听所有好友通道
 *  @param  无
 *
 *  @return 无
 */
void Adapt::adaptListenAllFriends()
{
    int ret = 0;
    Cache *c = gCtx.cache;
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (!z || !c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList_.begin(); it != c->friendList_.end(); it++) {
        Friend &f = it.value();
        ret = z->listen_friend(StringToHex(f.friendChannelId_.toStdString()));
        if (ret < 0) {
            std::cout << "c++: listen friend fail - " << f.friendChannelId_.toStdString() << std::endl;
            continue;
        }
        Utils::ShadowTalkSleep(200);
    }
    std::cout << "c++: listen all friends ok" << std::endl;
    return;
}

/**
 *  功能描述: 取消监听好友适配接口
 *  @param friendChannelId  好友通道id
 *
 *  @return 无
 */
void Adapt::adaptUnistenFriends(std::string friendChannelId)
{
    int ret = 0;
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (!z) {
        return;
    }
    ret = z->stop_listen_friend(friendChannelId);
    if (ret < 0) {
        std::cout << "c++: unlisten friend fail" << std::endl;
    }
    return;
}

/**
 *  功能描述: 取消监听所有好友
 *  @param  无
 *
 *  @return
 */
void Adapt::adaptUnlistenAllFriends()
{
    int ret = 0;
    Cache *c = gCtx.cache;
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (!z || !c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList_.begin(); it != c->friendList_.end(); it++) {
        Friend &f = it.value();
        ret = z->stop_listen_friend(StringToHex(f.friendChannelId_.toStdString()));
        if (ret < 0) {
            std::cout << "c++: unlisten all friend fail" << std::endl;
            continue;
        }
    }
    std::cout << "c++: unlisten all friends ok" << std::endl;
    return;
}

/**
 *  功能描述: 发送组消息
 *  @param  channelId    组id
 *  @param  messageType  消息类型
 *  @param  message      消息内容
 *  @param  myName       名字
 *
 *  @return
 */
void Adapt::adaptSendGroupMessage(QString channelId, int messageType, QString message, QString myName)
{
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (z) {
        z->send_group_message(StringToHex(channelId.toStdString()),
                              messageType, message.toStdString(),
                              60, 3600, QDateTime::currentMSecsSinceEpoch()/1000,
                              message.toStdString().size(), 0, myName.toStdString());
        qDebug() << "c++: adaptSendGroupMessage";
    }
    return;
}

/**
 *  功能描述: 监听组
 *  @param  groupChannelId    组id
 *
 *  @return
 */
void Adapt::adaptListenGroups(QString groupChannelId)
{
    Cache *c = gCtx.cache;
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (!z || !c) {
        return;
    }
    z->listen_group_channel(StringToHex(groupChannelId.toStdString()));
    std::cout << "c++: listen group ok" << std::endl;
    return;
}

/**
 *  功能描述: 监听所有组
 *  @param  无
 *
 *  @return
 */
void Adapt::adaptListenAllGroups()
{
    Cache *c = gCtx.cache;
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (!z || !c) {
        return;
    }

    QMap<int, Group>::iterator it;
    for (it = c->groupList_.begin(); it != c->groupList_.end(); it++) {
        Group &g = it.value();
        z->listen_group_channel(StringToHex(g.groupChannelId_.toStdString()));
        Utils::ShadowTalkSleep(300);
    }
    std::cout << "c++: listen all group ok" << std::endl;
    return;
}
