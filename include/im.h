#ifndef  IM_HPP_
#define  IM_HPP_

#include <string>
using namespace std;

namespace peersafe {
namespace im {


enum ImapiMessageType {
	ImapiMessageType_PCBackup = 7,
	ImapiMessageType_PCOffLine = 8,
	ImapiMessageType_SyncMessage = 9,
	ImapiMessageType_PingPC = 10,
	ImapiMessageType_ResponeFromPC = 11,

	ImapiMessageType_ForwadOffset = 1000,
    ImapiMessageType_ForwadSelfOffset = 2000,
};


class im_api_impl;
class Message_delegates {
public:
	/* 网络状态改变 */
	virtual void network_state(int stat_code) = 0;

	/* 好友上线或者离线状态 */
	virtual void friend_state(const string &friend_channel_id,
			int state_code) = 0;

	/* 接受离线消息 */
	virtual void friend_offline_message(const string &friend_channel_id, const int type,
			const string &message, unsigned long message_id,
            int expired, int entire_expired, int length, int timestamp) = 0;

	/* 接受在线消息 */
	virtual void friend_online_message(const string &friend_channel_id, const int type,
			const string &message, unsigned long message_id, 
            int expired, int entire_expired,int length, int timestamp) = 0;

	/* 接收添加好友请求 */
	virtual void friend_request_via_qr(const string &qr_channel_id,
			const string &info, const string &friend_channel_id) = 0;

	/* 解析邀请码对应的qrchannel的回调 */
	//virtual void qr_channel_via_short_code(const string &qr_channel_id) = 0;

	/* 好友请求是否被接受 */
	virtual void friend_request_reply(const string &friend_channel_id,
			bool accepted) = 0;

	/* 已被对方通知删除好友 */
	virtual void friend_deleted(const string &friend_channel_id) = 0;

	/* 数据操作 */
	virtual void store_data(const string &key_id, const string &read_data) = 0;
	virtual void read_data(const string &key_id, string &read_data) = 0;
	virtual void delete_data(const string &key_id) = 0;

	/* deduplication */
	virtual bool isExisted(const string &item, unsigned int expire) = 0;

    /* 数据是否发送成功 */
    virtual void handler_write_message_reply(const std::string &channel_id,
                                            unsigned long message_id,
                                            int ret_code) = 0;

    /* ice 通道状态 非0为异常 */
    virtual void ice_session_state(const std::string &channel_id, int state) = 0;

    /* 底层回调上层判断是否能通过无网通道发送，能则异步发送并返回1，否则返回-1 */
    virtual int send_message_via_direct_connection(const std::string &connection_id,
              const std::string &friend_channel_id, unsigned long message_id, const std::string &data) = 0;
    /* 底层通知上层绑定connection_id和friend_channel_id */
	virtual void bind_friend_channel(const std::string &connection_id, const std::string &friend_channel_id) = 0;

	//group chat
    //group chat invite from friend
    virtual void group_chat_invite_received(const std::string &friend_channel_id,
                                            const std::string &group_channel_id,
                                            const std::string &my_name) = 0;

    //group chat invite accepted by friend. friend_member_id will be empty if accepted = false
    virtual void group_chat_invite_reply_received(const std::string &friend_channel_id,
                                                  const std::string &group_channel_id,
                                                  bool accepted,
                                                  const std::string &friend_member_id) = 0;
    //new group member
    virtual void group_chat_member(const string &group_channel_id,
                                   const string &member_id,
                                   const std::string &name,
                                   unsigned long join_time) = 0;

    //group member removed
	virtual void group_chat_member_removed(const string &group_channel_id, const std::string &remover
        , const string &member_id, unsigned long removed_time) = 0;

    //group message
    virtual void group_chat_message_received(const string &group_channel_id,
                                             const string &author, const int type,
                                             const string &message, unsigned long message_id,
                                             int expired, int entire_expired,
                                             int length, int timestamp, const std::string &author_name) = 0;

    //group channel name
    virtual void group_channel_name_changed(const string &group_channel_id,
                                            const string &channel_name,
                                            unsigned long changed_time) = 0;
};

class Message_client {
public:
	Message_client();
	~Message_client();
	/* 初始化建立链接 */
	void init(const string &bootstrapContacts, Message_delegates *delegates, const std::string &ip17mon_db_path);

	/* 监听好友 */
	int listen_friend(const string &friend_channel_id);

	/* 停止监听好友 */
	int stop_listen_friend(const string &friend_channel_id);

	/* 申明自己的在线状态 */
	int announce_state(const string &friend_channel_id, int state_code);

	/* 发送离线消息 */
	unsigned long send_offline_message(const string &friend_channel_id, int message_type,
			const string &message, int expire = 0,
            int entire_expire = 0, int timestamp = 0, 
            int length = 0, unsigned long message_id = 0);

	/* 发送在线消息 */
	unsigned long send_online_message(const string &friend_channel_id, int message_type,
			const string &message, int expire = 0,
            int entire_expire = 0, int timestamp = 0, 
            int length = 0, unsigned long message_id = 0);

	/* 发送给pc的同步消息 */
	unsigned long send_sync_message(const string &pc_channel_id,
			const string &friend_channel_id, int message_type,
			const string &message, int expire = 0,
            int entire_expire = 0, int timestamp = 0,
            int length = 0, unsigned long message_id = 0);

    /* 生成随机唯一messageId */
    unsigned long get_next_message_id();
    
	/* 用于二维码建立channel通讯 */
	string generate_qr_channel(int expire); //错误同步返回空

	/* 用户短码交换邀请码 */
	string generate_short_code(const string &qr_channel_id, int expire);//错误同步返回空

	/* 监听用于好友申请的频道 */
	void listen_qr_channel(const string &qr_channel_id);

	/* 取消监听用于好友申请的频道 */
	void unlisten_qr_channel(const string &qr_channel_id);

	/* 删除邀请码 */
	int delete_qr_channel(const string &qr_channel_id);

	/* 添加好友，传入扫描二维码获得的qrChannelId及备注，正常返回friendChannel, 否则返回空字符串 */
	string add_friend_via_qr_channel(const string &qr_channel_id,
			const string &info);  //错误同步返回空,int返回值，加出参

	/* 添加好友, 临时邀请码添加方式 */
	string add_friend_via_short_code(const string &short_code,
			const string &info);//错误同步返回空,int返回值，加出参

	/* 上层选择是否接受好友请求 */
	int handle_friend_request(const string &friend_channel_id, bool result);

	/* 删除好友 */
	int delete_friend(const string &friend_channel_id, bool notify_friend);

    /* 上层收到附近设备的消息后，调用此接口通知底层处理消息并回调相关接口 */
	void direct_connection_message_received(const string &connection_id, const string &friend_channel_id, const string &data);
    /* 向附近的一个连接的发送好友请求 */
	std::string add_friend_via_direct_connection(const string &connection_id, const std::string &info);

	void check_messages();

	string hex_decode(const string &data);
	string hex_encode(const string &data);
    
    string base64Decode(const string &data);
    string base64Encode(const string &data);

    string gzipCompress(const string &data);
    string gzipUncompress(const string &data);
    
    string encrypt(const string &data, const string &pass);
    string decrypt(const string &data, const string &pass);
    
	int get_network_state();
    void enableLog();



	//group chat
	string create_group_channel(const std::string& group_channel_name, const std::string& my_name);	//create group
	int delete_group_channel(const std::string &group_channel_id, const std::string& info = "");	//delete group
	int set_group_channel_name(const std::string &group_channel_id, const std::string &group_channel_name);								//set name

	int invite_friend_to_group_chat(const std::string &friend_channel_id, const std::string &group_channel_id, const std::string &my_name);	//invite friend

	int remove_group_member(const std::string &group_channel_id, const std::string& member_id);

	int reply_group_chat_invite(const std::string &friend_channel_id, const std::string &group_channel_id, bool accept, const std::string &my_name);	//refuse/accept group chat invite

	unsigned long send_group_message(const std::string &group_channel_id, int message_type,		//send group message
		const string &message, int expire = 0,
		int entire_expire = 0, int timestamp = 0,
		int length = 0, unsigned long message_id = 0, const std::string &my_name="");

	std::string get_group_chat_local_id(const std::string &group_channel_id);					//get my member_id in group chat

	std::string get_group_channel_name(const std::string &group_channel_id);					//get groupName by groupChannelId

	void listen_group_channel(const string &group_channel_id);									//connect to a group chat so we can send/receive messages in this group chat

private:
	class im_api_impl *impl_;
};

}
}

#endif  /*IM_HPP_*/
