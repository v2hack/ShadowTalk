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

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

std::string StringToHex(std::string s) {
    peersafe::im::Message_client *z = gCtx.zebra;
    return z->hex_decode(s);
}

std::string HexToString(std::string s) {
    peersafe::im::Message_client *z = gCtx.zebra;
    if (!z) {
        std::cout << "zebra is null" << std::endl;
        return "";
    }
    return z->hex_encode(s);
}

zebraDeleagates::zebraDeleagates() {

}

zebraDeleagates::~zebraDeleagates() {

}

/* 网络状态改变 */
void zebraDeleagates::network_state(int stat_code) {
std:cout << "network_state - " << std::endl;

}

/* 好友上线或者离线状态 */
void zebraDeleagates::friend_state(
        const string &friend_channel_id,
        int state_code) {
    std::cout << "friend_state" << state_code << std::endl;
}

/* 接受离线消息 */
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
    playMessageSound();

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
        Friend &f = it.value();
        int idx = f.messageList.size() + 1;

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
                    addImageToWidget(f.id, f.name, type, 0, QString::fromStdString(m->data), idx);
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
                m->messageType = type;
                f.messageUnreadCount++;
                f.displayUnreadCount(f.id - 1, f.messageUnreadCount);
            }

            f.setTimeAndState(f.id - 1, MessageMethodOffline);
            f.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_offline_message", "receive one online message", f.id, message.c_str());
        }
    }
}

/* 接受在线消息 */
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
    playMessageSound();

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
        Friend &f = it.value();
        int idx = f.messageList.size() + 1;
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
                    addImageToWidget(f.id, f.name, type, 0, QString::fromStdString(m->data), idx);
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
                m->messageType = type;
                f.messageUnreadCount++;
                f.displayUnreadCount(f.id - 1, f.messageUnreadCount);
            }

            f.setTimeAndState(f.id - 1, MessageMethodOnline);
            f.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_online_message", "receive one online message", f.id, message.c_str());
        }
    }
}

/* 接收添加好友请求 */
void zebraDeleagates::friend_request_via_qr(
        const string &qr_channel_id,
        const string &info,
        const string &friend_channel_id)
{
    std::cout << "friend_request_via_qr" << std::endl;
}


/* 好友请求是否被接受 */
void zebraDeleagates::friend_request_reply(
        const string &friend_channel_id,
        bool accepted)
{
    std::cout << "friend_request_reply" << std::endl;
}

/* 已被对方通知删除好友 */
void zebraDeleagates::friend_deleted(const string &friend_channel_id)
{
    std::cout << "friend_deleted" << std::endl;
}


/* 数据操作 */
void zebraDeleagates::store_data(const string &key_id, const string &read_data)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList.find(key_id);
    if (it != c->keyValueList.end()) {
        it->second = read_data;
        std::cout << "update store key ok" << std::endl;
        return;
    } else {
        c->keyValueList.insert(std::pair<std::string, std::string>(key_id, read_data));
        std::cout << "insert key ok" << std::endl;
    }
}


void zebraDeleagates::read_data(const string &key_id, string &read_data)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList.find(key_id);
    if (it != c->keyValueList.end()) {
        std::cout << "find key ok - " << std::endl;
        read_data = it->second;
        return;
    }
    std::cout << "no find value" << std::endl;
    read_data.clear();
    return ;
}

void zebraDeleagates::delete_data(const string &key_id)
{
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

/* 去重函数 */
bool zebraDeleagates::isExisted(const string &item, unsigned int expire)
{
    static std::string zebraIsExisted;
    if (item == zebraIsExisted) {
        return true;
    } else {
        zebraIsExisted = item;
        return false;
    }
    return false;
}

/* 数据是否发送成功 */
void zebraDeleagates::handler_write_message_reply(
        const std::string &channel_id,
        unsigned long message_id, int ret_code)
{
    std::cout << "handler_write_message_reply" << std::endl;
}

/* ice 通道状态 非0为异常 */
void zebraDeleagates::ice_session_state(const std::string &channel_id, int state)
{
    std::cout << "ice_session_state" << std::endl;
}

/* 底层回调上层判断是否能通过无网通道发送，能则异步发送并返回1，否则返回-1 */
int zebraDeleagates::send_message_via_direct_connection(
        const std::string &connection_id,
        const std::string &friend_channel_id,
        unsigned long message_id,
        const std::string &data)
{
    std::cout << "send_message_via_direct_connection" << std::endl;
    return 0;
}

/* 底层通知上层绑定connection_id和friend_channel_id */
void zebraDeleagates::bind_friend_channel(
        const std::string &connection_id,
        const std::string &friend_channel_id)
{
    std::cout << "bind_friend_channel" << std::endl;
}
