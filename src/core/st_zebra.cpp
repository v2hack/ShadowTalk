#include <iostream>
#include <map>

#include "st_cache.h"
#include "st_context.h"
#include "st_zebra.h"

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
void zebraDeleagates::network_state(int stat_code)
{
std:cout << "network_state - " << std::endl;

}

/* 好友上线或者离线状态 */
void zebraDeleagates::friend_state(
        const string &friend_channel_id,
        int state_code)
{
    std::cout << "friend_state" << std::endl;


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
    std::cout << "delete_data" << std::endl;

}

/* deduplication */
bool zebraDeleagates::isExisted(const string &item, unsigned int expire)
{
    std::cout << "isExisted" << std::endl;

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
