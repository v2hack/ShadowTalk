/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_zebra.cpp
 *  简要描述:
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <iostream>
#include <map>

#include "st_cache.h"
#include "st_context.h"
#include "st_zebra.h"
#include "st_log.h"
#include "st_utils.h"
#include "st_parsexml.h"
#include "st_net.h"
#include "st_login.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 字符串转换为十六进制
 *  @param s 字符串
 *
 *  @return 无
 */
std::string StringToHex(std::string s) {
    peersafe::im::Message_client *z = gCtx.zebra;
    return z->hex_decode(s);
}

/**
 *  功能描述: HexToString
 *  @param s 字符串
 *
 *  @return 无
 */
std::string HexToString(std::string s) {
    peersafe::im::Message_client *z = gCtx.zebra;
    if (!z) {
        return "";
    }
    return z->hex_encode(s);
}

zebraDeleagates::zebraDeleagates() {

}

zebraDeleagates::~zebraDeleagates() {

}

/**
 *  功能描述: 网络状态
 *  @param stat_code 状态、值
 *
 *  @return 无
 */
void zebraDeleagates::network_state(int stat_code) {
std:cout << "network_state - " << std::endl;
}

/**
 *  功能描述: 好友上线或者离线状态
 *  @param friend_channel_id 好友通道id
 *  @param state_code 状态值
 *
 *  @return 无
 */
void zebraDeleagates::friend_state(
        const string &friend_channel_id,
        int state_code) {
    std::cout << "friend_state" << state_code << std::endl;
}


/**
 *  功能描述: 处理手机端的特殊指令
 *  @param type 指令类型
 *  @param message 消息内容
 *
 *  @return 无
 */
int processPhoneCommand(int type, const string &message, const string &channel_id) {
    switch (type) {
	case MessagetypePCBackup:
	{
        /* 加载XML文件 */
        string passwd = gCtx.zebra->hex_encode(channel_id);
        writeXmlFile(SHADOW_SYNC_FILE, message);
        if (parseEncryptXml(QString(SHADOW_SYNC_FILE), QString::fromStdString(passwd)) < 0) {
            std::cout << "parse xml fail : passwd - " << passwd << std::endl;
            return -1;
        }
        /* 切换二维码为进度条 */
        ShadowTalkLoginStartSync();

        /* 加载动画走起 */
        for (int i = 0 ; i < 360; i++) {
            ShadowTalkSleep(1);
            ShadowTalkSetSyncProcess(i);
        }

        /* 切换到聊天界面 */
        displayBaseView();
        return 1;
	}
    case MessagetypePCOffLine:
    {
        // 取消监听所有好友

        // 不再收消息

        // 清理所有缓存

        // 清理界面

        displayLoginView();
        return 1;
    }
    case MessagetypePingPC:
    {
        gCtx.zebra->send_online_message(channel_id, MessagetypeResponeFromPC, "",
            60, 3600, QDateTime::currentMSecsSinceEpoch()/1000, 0, 0);
        return 1;
    }
    default:
        return 0;
    }
}

/**
 *  功能描述: 接受离线消息
 *  @param friend_channel_id 好友通道id
 *  @param type              消息类型
 *  @param message           消息内容
 *  @param message_id        消息id
 *  @param expired           过期时间
 *  @param entire_expired
 *  @param length            消息长度
 *  @param timestamp         时间戳
 *
 *  @return 无
 */
void zebraDeleagates::friend_offline_message(
        const string &friend_channel_id,
        const int type,
        const string &message,
        unsigned long message_id,
        int expired,
        int entire_expired,
        int length,
        int timestamp)
{
    std::cout << "friend_offline_message" << std::endl;

    int ret = 0;
    ret = processPhoneCommand(type, message, friend_channel_id);
    if (ret < 0 || ret == 1) {
        return;
    }

    playMessageSound();

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
        Friend &f = it.value();
        int idx = f.messageList.size();

        if (friend_channel_id == StringToHex(f.friendChannelId.toStdString())) {
            Message *m        = new Message;
            m->data           = message;
            m->driect         = 0;
            m->messageType    = MessageTypeNone;
            m->MessageMethord = MessageMethodOffline;
            m->voiceSeconds   = 0;

            f.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_offline_message", "receive one online message", f.id, message.c_str());

            /* 如果是当前界面显示的好友，那么添加到界面，否则不加 */
            if (c->currentUseFriendId == f.id) {
                f.messageUnreadCount = 0;

                /* 判断类型 */
                switch (type) {
                case MessageTypeWord:
                    m->messageType = MessageTypeWord;
                    addMessageToWidget(f.id, f.name, type, 0, QString::fromStdString(m->data), idx);
                    break;
                case MessageTypeImage:
                    m->messageType = MessageTypeImage;
                    addImageToWidget(f.id, f.name, type, 0, m->data, idx);
                    break;
                case MessageTypeVoice:
                    m->messageType = MessageTypeVoice;
                    m->voiceSeconds = length;
                    addVoiceToWidget(f.id, f.name, type, 0, QString::fromStdString(m->data), length, idx);
                    break;
                default:
                    break;
                }
            } else {
                f.messageUnreadCount++;
                f.displayUnreadCount(f.id - 1, f.messageUnreadCount);
                /* 判断类型 */
                switch (type) {
                case MessageTypeWord:
                    m->messageType = MessageTypeWord;
                    break;
                case MessageTypeImage:
                    m->messageType = MessageTypeImage;
                    break;
                case MessageTypeVoice:
                    m->messageType = MessageTypeVoice;
                    m->voiceSeconds = length;
                    break;
                default:
                    break;
                }
            }
            f.setTimeAndState(f.id - 1, MessageMethodOffline);
            f.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_offline_message", "receive one online message", f.id, message.c_str());
        }
    }
}


/**
 *  功能描述: 接受在线消息
 *  @param friend_channel_id 好友通道id
 *  @param type              消息类型
 *  @param message           消息内容
 *  @param message_id        消息id
 *  @param expired           过期时间
 *  @param entire_expired
 *  @param length            消息长度
 *  @param timestamp         时间戳
 *
 *  @return 无
 */
void zebraDeleagates::friend_online_message(
        const string &friend_channel_id,
        const int type,
        const string &message,
        unsigned long message_id,
        int expired,
        int entire_expired,
        int length,
        int timestamp)
{
    std::cout << "friend_online_message" << std::endl;
    int ret = 0;
    ret = processPhoneCommand(type, message, friend_channel_id);
    if (ret < 0 || ret == 1) {
        return;
    }

    playMessageSound();

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
        Friend &f = it.value();
        int idx = f.messageList.size();
        if (friend_channel_id == StringToHex(f.friendChannelId.toStdString())) {

            Message *m        = new Message;
            m->data           = message;
            m->driect         = 0;
            m->messageType    = MessageTypeNone;
            m->MessageMethord = MessageMethodOnline;
            m->voiceSeconds   = 0;

            /* 如果是当前界面显示的好友，那么添加到界面，否则不加 */
            if (c->currentUseFriendId == f.id) {
                f.messageUnreadCount = 0;

                /* 判断类型 */
                switch (type) {
                case MessageTypeWord:
                    m->messageType = MessageTypeWord;
                    addMessageToWidget(f.id, f.name, type, 0, QString::fromStdString(m->data), idx);
                    break;
                case MessageTypeImage:
                    m->messageType = MessageTypeImage;
                    addImageToWidget(f.id, f.name, type, 0, m->data, idx);
                    break;
                case MessageTypeVoice:
                    m->messageType = MessageTypeVoice;
                    m->voiceSeconds = length;
                    addVoiceToWidget(f.id, f.name, type, 0, QString::fromStdString(m->data), length, idx);
                    break;
                default:
                    break;
                }
            } else {
                f.messageUnreadCount++;
                f.displayUnreadCount(f.id - 1, f.messageUnreadCount);
                /* 判断类型 */
                switch (type) {
                case MessageTypeWord:
                    m->messageType = MessageTypeWord;
                    break;
                case MessageTypeImage:
                    m->messageType = MessageTypeImage;
                    break;
                case MessageTypeVoice:
                    m->messageType = MessageTypeVoice;
                    m->voiceSeconds = length;
                    break;
                default:
                    break;
                }
            }

            f.setTimeAndState(f.id - 1, MessageMethodOnline);
            f.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_online_message", "receive one online message", f.id, message.c_str());
        }
    }
}


/**
 *  功能描述: 接收添加好友请求
 *  @param qr_channel_id     二维码通道id
 *  @param info              消息内容
 *  @param friend_channel_id 好友通道id
 *
 *  @return 无
 */
void zebraDeleagates::friend_request_via_qr(
        const string &qr_channel_id,
        const string &info,
        const string &friend_channel_id) {

    if (gCtx.phoneQrChannel != qr_channel_id) {
        std::cout << "is not sync channel id";
        return;
    }
    gCtx.zebra->handle_friend_request(friend_channel_id, true);
    gCtx.zebra->listen_friend(friend_channel_id);
    gCtx.phoneSyncChannel = friend_channel_id;
    std::cout << "accept sync channel request" << std::endl;
    return;
}


/**
 *  功能描述: 好友请求是否被接受
 *  @param friend_channel_id 好友通道id
 *  @param accepted          对方是否接受添加
 *
 *  @return 无
 */
void zebraDeleagates::friend_request_reply(
        const string &friend_channel_id,
        bool accepted) {
    std::cout << "friend_request_reply" << std::endl;
}


/**
 *  功能描述: 已被对方通知删除好友
 *  @param friend_channel_id 好友通道id
 *
 *  @return 无
 */
void zebraDeleagates::friend_deleted(const string &friend_channel_id) {
    std::cout << "friend_deleted" << std::endl;
}

/**
 *  功能描述: 存储数据操作
 *  @param key_id     key索引
 *  @param read_data  key数值
 *
 *  @return 无
 */
void zebraDeleagates::store_data(const string &key_id, const string &read_data) {
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList.find(key_id);
    if (it != c->keyValueList.end()) {
        it->second = read_data;
        return;
    } else {
        c->keyValueList.insert(std::pair<std::string, std::string>(key_id, read_data));
    }
}

/**
 *  功能描述: 存储数据读取
 *  @param key_id     key索引
 *  @param read_data  key数值
 *
 *  @return 无
 */
void zebraDeleagates::read_data(const string &key_id, string &read_data) {
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList.find(key_id);
    if (it != c->keyValueList.end()) {
        read_data = it->second;
        return;
    }
    read_data.clear();
    return;
}

/**
 *  功能描述: 存储数据读取
 *  @param key_id     key索引
 *  @param read_data  key数值
 *
 *  @return 无
 */
void zebraDeleagates::delete_data(const string &key_id) {
    int deleteFlag = 0;
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList.find(key_id);
    if (it != c->keyValueList.end()) {
        deleteFlag = 1;
    }
    c->keyValueList.erase(key_id);
    return;
}

/**
 *  功能描述: 去重函数
 *  @param item    去重数值
 *  @param expire  超期时间
 *
 *  @return 无
 */
bool zebraDeleagates::isExisted(const string &item, unsigned int expire) {
    static std::string zebraIsExisted;
    if (item == zebraIsExisted) {
        return true;
    } else {
        zebraIsExisted = item;
        return false;
    }
    return false;
}

/**
 *  功能描述: 数据是否发送成功
 *  @param channel_id  通道索引
 *  @param message_id  消息索引
 *  @param ret_code    处理结果
 *
 *  @return 无
 */
void zebraDeleagates::handler_write_message_reply(
        const std::string &channel_id,
        unsigned long message_id, int ret_code) {
    std::cout << "handler_write_message_reply" << std::endl;
}


/**
 *  功能描述: ice 通道状态 非0为异常
 *  @param channel_id  通道索引
 *  @param state       ice状态
 *  @param ret_code    处理结果
 *
 *  @return 无
 */
void zebraDeleagates::ice_session_state(const std::string &channel_id, int state) {
    std::cout << "ice_session_state" << std::endl;
}


/**
 *  功能描述: 底层回调上层判断是否能通过无网通道发送，能则异步发送并返回1，否则返回 -1
 *  @param connection_id       连接id
 *  @param friend_channel_id   超有通道id
 *  @param message_id          消息id
 *  @param data                数据内容
 *
 *  @return 无
 */
int zebraDeleagates::send_message_via_direct_connection(
        const std::string &connection_id,
        const std::string &friend_channel_id,
        unsigned long message_id,
        const std::string &data)
{
    std::cout << "send_message_via_direct_connection" << std::endl;
    return 0;
}


/**
 *  功能描述: 底层通知上层绑定connection_id和friend_channel_id
 *  @param connection_id       连接id
 *  @param friend_channel_id   超有通道id
 *
 *  @return 无
 */
void zebraDeleagates::bind_friend_channel(
        const std::string &connection_id,
        const std::string &friend_channel_id)
{
    std::cout << "bind_friend_channel" << std::endl;
}
