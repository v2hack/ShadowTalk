#ifndef  IM_HPP_
#define  IM_HPP_

#include <string>
using namespace std;

namespace peersafe {
namespace im {

enum ImapiMessageType
{
    ImapiMessageType_PCBackup           = 7,       /* 同步文件 */
    ImapiMessageType_PCOffLine          = 8,       /* 让PC端离线 */
    ImapiMessageType_SyncMessage        = 9,       /* 同步消息 */
    ImapiMessageType_PingPC             = 10,      /* ping客户端是否存在 */
    ImapiMessageType_ResponeFromPC      = 11,      /* ping的相应 */
    ImapiMessageType_DeleteFriend       = 12,      /* 删除好友 */
    ImapiMessageType_AddFriendRequest   = 13,      /* 加好友请求 */
    ImapiMessageType_AddFriendReply     = 14,      /* 加好友回复 */

    ImapiMessageType_ForwadOffset       = 1000,    /* 同步消息偏移 */
    ImapiMessageType_ForwadSelfOffset   = 2000,    /* 同步自己的消息偏移 */

    ImapiMessageType_SyncGroupMessage   = 100,      /* 组消息同步 */
    ImapiMessageType_GroupInviteRequest = 101,      /* 组邀请 */
    ImapiMessageType_GroupInviteReply   = 102,      /* 组邀请恢复 */
    ImapiMessageType_GroupNewMember     = 103,      /* 组新成员 */
    ImapiMessageType_GroupRemoveMember  = 104,      /* 移除组成员 */
    ImapiMessageType_GroupMessage       = 105,      /* 组消息 */
    ImapiMessageType_GroupChangeName    = 106,      /* 组消息 */

    ImapiMessageType_ForwadGOffset      = 3000,     /* 组同步偏移 */
    ImapiMessageType_ForwadGSelfOffset  = 4000,     /* 组同步自己的消息偏移 */
};


class im_api_impl;

/* zebra回调类 */
class Message_delegates
{
public:
    /* 网络状态改变 */
    virtual void network_state(int stat_code) = 0;

    /* 好友上线或者离线状态 */
    virtual void friend_state(
            const string &friend_channel_id,
            int state_code) = 0;

    /* 接受离线消息 */
    virtual void friend_offline_message(
            const string &friend_channel_id,
            const int type,
            const string &message,
            unsigned long message_id,
            int expired,
            int entire_expired,
            int length,
            int timestamp) = 0;

    /* 接受在线消息 */
    virtual void friend_online_message(
            const string &friend_channel_id,
            const int type,
            const string &message,
            unsigned long message_id,
            int expired,
            int entire_expired,
            int length,
            int timestamp) = 0;

    /* 接收添加好友请求 */
    virtual void friend_request_via_qr(
            const string &qr_channel_id,
            const string &info,
            const string &friend_channel_id) = 0;

    /* 好友请求是否被接受 */
    virtual void friend_request_reply(
            const string &friend_channel_id,
            bool accepted) = 0;

    /* 已被对方通知删除好友 */
    virtual void friend_deleted(const string &friend_channel_id) = 0;

    /* 存储数据回调 */
    virtual void store_data(
            const string &key_id,
            const string &read_data) = 0;

    /* 读取数据回调 */
    virtual void read_data(
            const string &key_id,
            string &read_data) = 0;

    /* 删除数据回调 */
    virtual void delete_data(const string &key_id) = 0;

    /* 重复数据检查 */
    virtual bool isExisted(
            const string &item,
            unsigned int expire) = 0;

    /* 数据是否发送成功 */
    virtual void handler_write_message_reply(
            const std::string &channel_id,
            unsigned long message_id,
            int ret_code) = 0;

    /* ice 通道状态 非0为异常 */
    virtual void ice_session_state(
            const std::string &channel_id,
            int state) = 0;

    /* 底层回调上层判断是否能通过无网通道发送，
     * 能则异步发送并返回1，否则返回-1 */
    virtual int send_message_via_direct_connection(
            const std::string &connection_id,
            const std::string &friend_channel_id,
            unsigned long message_id,
            const std::string &data) = 0;

    /* 底层通知上层绑定connection_id和friend_channel_id */
    virtual void bind_friend_channel(
            const std::string &connection_id,
            const std::string &friend_channel_id) = 0;

    /* 接收到组邀请 */
    virtual void group_chat_invite_received(
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            const std::string &my_name) = 0;

    /* 接收到组邀请的回复 */
    virtual void group_chat_invite_reply_received(
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            bool accepted,
            const std::string &friend_member_id) = 0;

    /* 组添加成员 */
    virtual void group_chat_member(
            const string &group_channel_id,
            const string &member_id,
            const std::string &name,
            unsigned long join_time) = 0;

    /* 组成员移除 */
    virtual void group_chat_member_removed(
            const string &group_channel_id,
            const std::string &remover,
            const string &member_id,
            unsigned long removed_time) = 0;

    /* 接收到组消息 */
    virtual void group_chat_message_received(
            const string &group_channel_id,
            const string &author, const int type,
            const string &message,
            unsigned long message_id,
            int expired,
            int entire_expired,
            int length,
            int timestamp,
            const std::string &author_name) = 0;

    /* 群名字改变 */
    virtual void group_channel_name_changed(
            const string &group_channel_id,
            const string &channel_name,
            unsigned long changed_time) = 0;
};

/* zebra 接口 */
class Message_client
{
public:
    Message_client();
    ~Message_client();
    /* 初始化建立链接 */
    void init(const string &bootstrapContacts,
              Message_delegates *delegates,
              const std::string &ip17mon_db_path);

    /* 监听好友 */
    int listen_friend(const string &friend_channel_id);

    /* 停止监听好友 */
    int stop_listen_friend(const string &friend_channel_id);

    /* 申明自己的在线状态 */
    int announce_state(
            const string &friend_channel_id,
            int state_code);

    /* 发送离线消息 */
    unsigned long send_offline_message(
            const string &friend_channel_id,
            int message_type,
            const string &message,
            int expire = 0,
            int entire_expire = 0,
            int timestamp = 0,
            int length = 0,
            unsigned long message_id = 0);

    /* 发送在线消息 */
    unsigned long send_online_message(
            const string &friend_channel_id,
            int message_type,
            const string &message,
            int expire = 0,
            int entire_expire = 0,
            int timestamp = 0,
            int length = 0,
            unsigned long message_id = 0);

    /* 发送给pc的同步消息 */
    unsigned long send_sync_message(
            const string &pc_channel_id,
            const string &friend_channel_id,
            int message_type,
            const string &message,
            int expire = 0,
            int entire_expire = 0,
            int timestamp = 0,
            int length = 0,
            unsigned long message_id = 0);

    /* 生成随机唯一messageId */
    unsigned long get_next_message_id();
    
    /* 用于二维码建立channel通讯 */
    string generate_qr_channel(int expire);

    /* 用户短码交换邀请码 */
    string generate_short_code(
            const string &qr_channel_id,
            int expire);

    /* 监听用于好友申请的频道 */
    void listen_qr_channel(const string &qr_channel_id);

    /* 取消监听用于好友申请的频道 */
    void unlisten_qr_channel(const string &qr_channel_id);

    /* 删除邀请码 */
    int delete_qr_channel(const string &qr_channel_id);

    /* 添加好友，传入扫描二维码获得的qrChannelId及备注，
     * 正常返回friendChannel, 否则返回空字符串 */
    string add_friend_via_qr_channel(
            const string &qr_channel_id,
            const string &info);  //错误同步返回空,int返回值，加出参

    /* 添加好友, 临时邀请码添加方式 */
    string add_friend_via_short_code(
            const string &short_code,
            const string &info);//错误同步返回空,int返回值，加出参

    /* 上层选择是否接受好友请求 */
    int handle_friend_request(
            const string &friend_channel_id,
            bool result);

    /* 删除好友 */
    int delete_friend(
            const string &friend_channel_id,
            bool notify_friend);

    /* 上层收到附近设备的消息后，调用此接口通知底层处理消息并回调相关接口 */
    void direct_connection_message_received(
            const string &connection_id,
            const string &friend_channel_id,
            const string &data);

    /* 向附近的一个连接的发送好友请求 */
    std::string add_friend_via_direct_connection(
            const string &connection_id,
            const std::string &info);

    void check_messages();

    /* 字符串十六进制处理 */
    string hex_decode(const string &data);
    string hex_encode(const string &data);

    /* 编码处理接口 */
    string base64Decode(const string &data);
    string base64Encode(const string &data);
    /* 压缩接口 */
    string gzipCompress(const string &data);
    string gzipUncompress(const string &data);

    /* 加密解密接口 */
    string encrypt(const string &data, const string &pass);
    string decrypt(const string &data, const string &pass);
    
    /* 获取网络状态 */
    int get_network_state();

    /* 启动底层日志 */
    void enableLog();

    /* 新建组 */
    string create_group_channel(
            const std::string& group_channel_name,
            const std::string& my_name);

    /* 删除组 */
    int delete_group_channel(
            const std::string &group_channel_id,
            const std::string& info = "");

    /* 设置组的通道名称 */
    int set_group_channel_name(
            const std::string &group_channel_id,
            const std::string &group_channel_name);

    /* 邀请好友加入组 */
    int invite_friend_to_group_chat(
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            const std::string &my_name);

    /* 删除组成员 */
    int remove_group_member(
            const std::string &group_channel_id,
            const std::string& member_id);

    /* 接受或者拒绝组邀请 */
    int reply_group_chat_invite(
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            bool accept,
            const std::string &my_name);

    /* 发送组消息 */
    unsigned long send_group_message(
            const std::string &group_channel_id,
            int message_type,
            const string &message,
            int expire = 0,
            int entire_expire = 0,
            int timestamp = 0,
            int length = 0,
            unsigned long message_id = 0,
            const std::string &my_name="");

    /* 获取组中的成员id */
    std::string get_group_chat_local_id(
            const std::string &group_channel_id);

    /* 根据组id获取组名字 */
    std::string get_group_channel_name(
            const std::string &group_channel_id);

    /* 监听组 */
    void listen_group_channel(const string &group_channel_id);


    /* 同步接收组邀请的消息 */
    void sync_group_chat_invite_received(
            const std::string &pc_channel_id,
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            const std::string &my_name);

    /* 同步组邀请回复的消息 */
    void sync_group_chat_invite_reply_received(
            const std::string &pc_channel_id,
            const std::string &friend_channel_id,
            const std::string &group_channel_id,
            bool accepted,
            const std::string &friend_member_id);

    /* 同步新加成员消息 */
    void sync_group_chat_member(
            const std::string &pc_channel_id,
            const std::string &group_channel_id,
            const std::string &member_id,
            const std::string &name,
            unsigned long join_time);

    /* 同步删除成员消息 */
    void sync_group_chat_member_removed(
            const std::string &pc_channel_id,
            const std::string &group_channel_id,
            const std::string &remover_id,
            const std::string &member_id,
            unsigned long removed_time);

    /* 同步组消息 */
    void sync_group_chat_message_received(
            const std::string &pc_channel_id,
            const std::string &group_channel_id,
            const std::string &author,
            int type,
            const std::string &message,
            unsigned long message_id,
            int expired,
            int entire_expired,
            int length,
            int timestamp,
            const std::string &author_name);

    /* 同步组名改变消息 */
    void sync_group_channel_name_changed(
            const std::string &pc_channel_id,
            const std::string &group_channel_id,
            const std::string &channel_name,
            unsigned long changed_time);

private:
    class im_api_impl *impl_;
};

}
}

#endif  /*IM_HPP_*/
