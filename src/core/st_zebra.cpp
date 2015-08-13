#include "st_zebra.h"



zebraDeleagates::zebraDeleagates() {

}

zebraDeleagates::~zebraDeleagates() {

}

/* 网络状态改变 */
void zebraDeleagates::network_state(int stat_code)
{

}

/* 好友上线或者离线状态 */
void zebraDeleagates::friend_state(
        const string &friend_channel_id,
        int state_code)
{


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



}

/* 接收添加好友请求 */
void zebraDeleagates::friend_request_via_qr(
        const string &qr_channel_id,
        const string &info,
        const string &friend_channel_id)
{


}


/* 好友请求是否被接受 */
void zebraDeleagates::friend_request_reply(
        const string &friend_channel_id,
        bool accepted)
{


}

/* 已被对方通知删除好友 */
void zebraDeleagates::friend_deleted(const string &friend_channel_id)
{


}

/* 数据操作 */
void zebraDeleagates::store_data(const string &key_id, const string &read_data)
{


}

void zebraDeleagates::read_data(const string &key_id, string &read_data)
{

}

void zebraDeleagates::delete_data(const string &key_id)
{


}

/* deduplication */
bool zebraDeleagates::isExisted(const string &item, unsigned int expire)
{
    return true;

}

/* 数据是否发送成功 */
void zebraDeleagates::handler_write_message_reply(
        const std::string &channel_id,
        unsigned long message_id, int ret_code)
{


}

/* ice 通道状态 非0为异常 */
void zebraDeleagates::ice_session_state(const std::string &channel_id, int state)
{


}

/* 底层回调上层判断是否能通过无网通道发送，能则异步发送并返回1，否则返回-1 */
int zebraDeleagates::send_message_via_direct_connection(
        const std::string &connection_id,
        const std::string &friend_channel_id,
        unsigned long message_id,
        const std::string &data)
{

    return 0;
}
/* 底层通知上层绑定connection_id和friend_channel_id */
void zebraDeleagates::bind_friend_channel(
        const std::string &connection_id,
        const std::string &friend_channel_id)
{


}
