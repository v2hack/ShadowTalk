#ifndef ZEBRA_H
#define ZEBRA_H

#include "peersafe/imapi/im.h"

using namespace peersafe::im;
using namespace std;

std::string StringToHex(std::string s);
std::string HexToString(std::string s);

class zebraDeleagates : public peersafe::im::Message_delegates
{
public:
    zebraDeleagates();
    ~zebraDeleagates();
    /* 网络状态改变 */
    virtual void network_state(int stat_code);
    /* 好友上线或者离线状态 */
    virtual void friend_state(
            const string &friend_channel_id,
            int state_code);

    /* 接受离线消息 */
    virtual void friend_offline_message(
            const string &friend_channel_id,
            const int type,
            const string &message,
            unsigned long message_id,
            int expired,
            int entire_expired,
            int length,
            int timestamp);

    /* 接受在线消息 */
    virtual void friend_online_message(
            const string &friend_channel_id,
            const int type,
            const string &message,
            unsigned long message_id,
            int expired,
            int entire_expired,
            int length,
            int timestamp);
    /* 接收添加好友请求 */
    virtual void friend_request_via_qr(
            const string &qr_channel_id,
            const string &info,
            const string &friend_channel_id);

    /* 好友请求是否被接受 */
    virtual void friend_request_reply(
            const string &friend_channel_id,
            bool accepted);

    /* 已被对方通知删除好友 */
    virtual void friend_deleted(const string &friend_channel_id);
    /* 数据操作 */
    virtual void store_data(const string &key_id, const string &read_data);
    virtual void read_data(const string &key_id, string &read_data);
    virtual void delete_data(const string &key_id);

    /* deduplication */
    virtual bool isExisted(const string &item, unsigned int expire);

    /* 数据是否发送成功 */
    virtual void handler_write_message_reply(
            const std::string &channel_id,
            unsigned long message_id, int ret_code);
    /* ice 通道状态 非0为异常 */
    virtual void ice_session_state(const std::string &channel_id, int state);

    /* 底层回调上层判断是否能通过无网通道发送，能则异步发送并返回1，否则返回-1 */
    virtual int send_message_via_direct_connection(
            const std::string &connection_id,
            const std::string &friend_channel_id,
            unsigned long message_id,
            const std::string &data);
    /* 底层通知上层绑定connection_id和friend_channel_id */
    virtual void bind_friend_channel(
            const std::string &connection_id,
            const std::string &friend_channel_id);

    //group chat
    //group chat invite from friend
    virtual void group_chat_invite_received(
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            const std::string &my_name);

    //group chat invite accepted by friend. friend_member_id will be empty if accepted = false
    virtual void group_chat_invite_reply_received(
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            bool accepted,
            const std::string &friend_member_id);

    //new group member
    virtual void group_chat_member(
            const string &group_channel_id,
            const string &member_id,
            const std::string &name,
            unsigned long join_time);

    //group member removed
    virtual void group_chat_member_removed(
            const string &group_channel_id,
            const std::string &remover,
            const string &member_id,
            unsigned long removed_time);

    //group message
    virtual void group_chat_message_received(
            const string &group_channel_id,
            const string &author,
            const int type,
            const string &message,
            unsigned long message_id,
            int expired,
            int entire_expired,
            int length,
            int timestamp,
            const std::string &author_name);

    //group channel name
    virtual void group_channel_name_changed(
            const string &group_channel_id,
            const string &channel_name,
            unsigned long changed_time);

    //send file result
    virtual int send_file_result(
            const int result,
            unsigned long fileid,
            const std::string &channel_id);

    virtual int recv_file_result(
            const int result,
            const std::string &channel_id,
            const std::string &digest);

    //Description  The callback was invoked
    // when filestream recieved digest.
    virtual int handle_file_digest(
            const std::string &channel_id,
            const std::string &digest,
            std::string &path);

    virtual int handle_send_file_process(
            const std::string &channel_id,
            unsigned long fileid,
            long offset);

    virtual int handle_recv_file_process(
            const std::string &channel_id,
            const std::string &digest,
            long offset);
};


#endif // ZEBRA_H

