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
#include <QThread>
#include <QDebug>
#include <QMutex>

#include <map>
#include <set>

#include "maidsafe/common/active.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_zebra.h"
#include "st_log.h"
#include "st_utils.h"
#include "st_parsexml.h"
#include "st_net.h"
#include "st_login.h"
#include "st_chat.h"
#include "st_thread.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;
/* asio 异步处理 */
maidsafe::Active g_io_service;
/* 用于调试信息打印 */
static unsigned long long _countMessage = 0;

/**
 *  功能描述: 字符串转换为十六进制
 *  @param s 字符串
 *
 *  @return 无
 */
std::string StringToHex(std::string s)
{
    peersafe::im::Message_client *z = gCtx.zebra_;
    return z->hex_decode(s);
}

/**
 *  功能描述: HexToString
 *  @param s 字符串
 *
 *  @return 无
 */
std::string HexToString(std::string s)
{
    peersafe::im::Message_client *z = gCtx.zebra_;
    if (!z) {
        return "";
    }
    return z->hex_encode(s);
}

zebraDeleagates::zebraDeleagates() {}
zebraDeleagates::~zebraDeleagates() {}

/**
 *  功能描述: 网络状态
 *  @param stat_code 状态、值
 *
 *  @return 无
 */
void zebraDeleagates::network_state(int stat_code)
{
    qDebug() << "c++: network_state - " <<  stat_code;
    return;
}

/**
 *  功能描述: 好友上线或者离线状态
 *  @param friend_channel_id 好友通道id
 *  @param state_code 状态值
 *
 *  @return 无
 */
void zebraDeleagates::friend_state(const string &friend_channel_id, int state_code)
{
    qDebug() << "c++: friend_state - " << state_code;
}

/**
 *  功能描述: 处理手机端的特殊指令
 *  @param type 指令类型
 *  @param message 消息内容
 *
 *  @return 无
 */
int processPhoneCommandEX(int type, const string &message, const string &channel_id){
    switch (type) {
    case MessagetypePCBackup:
    {

        if (gCtx.loadXmlFlag_ == 1) {
            qDebug() << "c++: it is loading xml file";
            return -1;
        }
        /* 加载XML文件 */
        string channel_id_128 = gCtx.zebra_->hex_encode(channel_id);
        string passwd = channel_id_128.substr(0, 16);
        //close by hsf 2015-11-11 改为从send_file_to获取文件
        //ParseXml::writeXmlFile(SHADOW_SYNC_FILE, message);
        //std::cout << "c++: xml file size - " << message.size() << std::endl;
        //std::cout << "c++: parse xml : passwd - " << passwd << std::endl;
        qDebug() << "c++: begin loading xml file";

        if (ParseXml::parseEncryptXml(QString(SHADOW_SYNC_FILE), QString::fromStdString(passwd)) < 0) {
            std::cout << "c++: parse xml file fail" << std::endl;
            return -1;
        }
         qDebug() << "c++: begin loading qrCode";
        /* 切换二维码为进度条 */
        Login::ShadowTalkLoginStartSync();
        /* 加载动画走起 */
        for (int i = 0 ; i < 360; i++) {
            Utils::ShadowTalkSleep(3);
            Login::ShadowTalkSetSyncProcess(i);
        }
        /* 切换到聊天界面 */
        gCtx.changeFlag_  = 1; /* 通知线程切换窗口 */
        gCtx.windowFlag_  = 2; /* 当前应该显示主窗口 */
        gCtx.loadXmlFlag_ = 0; /* 允许再次加载xml文件 */
        return 1;
    }
    default:
        return 0;
    }
}

/**
 *  功能描述: 处理手机端的特殊指令
 *  @param type 指令类型
 *  @param message 消息内容
 *
 *  @return 无
 */
int processPhoneCommand(int type, const string &message, const string &channel_id)
{
    switch (type) {
    case MessagetypePCBackup:
    {

        /* 加载XML文件 */
              string channel_id_128 = gCtx.zebra_->hex_encode(channel_id);
              string passwd = channel_id_128.substr(0, 16);
              ParseXml::writeXmlFile(SHADOW_SYNC_FILE, message);
              std::cout << "c++: xml file size - " << message.size() << std::endl;
              std::cout << "c++: parse xml : passwd - " << passwd << std::endl;

              if (ParseXml::parseEncryptXml(QString(SHADOW_SYNC_FILE), QString::fromStdString(passwd)) < 0) {
                  std::cout << "c++: parse xml file fail" << std::endl;
                  return -1;
              }
              /* 切换二维码为进度条 */
              Login::ShadowTalkLoginStartSync();
              /* 加载动画走起 */
              for (int i = 0 ; i < 360; i++) {
                  Utils::ShadowTalkSleep(3);
                  Login::ShadowTalkSetSyncProcess(i);
              }
              /* 切换到聊天界面 */
              gCtx.changeFlag_ = 1; /* 通知线程切换窗口 */
              gCtx.windowFlag_ = 2; /* 当前应该显示主窗口 */
              return 1;
    }
    case MessagetypePCOffLine:
    {
        qDebug() << "c++: set pc offline";
        /* 不再收消息 */
        setReceiveEnable(false);
        /* 取消监听所有好友 */
        Adapt::adaptUnlistenAllFriends();
        /* 恢复登录界面 */
        Login::ShadowTalkLoginClean();
        /* 变为登录界面 */
        Utils::displayLoginView();
        /* 清理界面 */
        Utils::ShadowTalkSleep(500);
        MessageWidget::clearMessageFromWidget();
        MessageWidget::clearFriendFromWidget();
        /* 清理所有缓存 */
        gCtx.cache->CleanCache();
        return 1;
    }
    case MessagetypePingPC:
    {
        qDebug() << "c++: receive pc ping";
        gCtx.zebra_->send_online_message(gCtx.phoneSyncChannel, MessagetypeResponeFromPC,
                                        "respone", 60, 3600, QDateTime::currentMSecsSinceEpoch()/1000, 7, 0);
        gCtx.phoneUpdateTime.restart();
        return 1;
    }
    default:
        return 0;
    }
}

/**
 *  功能描述: 根据手机在线状态进行消息的转发
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
void forwardMessage(const string &friend_channel_id, const int type, const string &message,
                    unsigned long message_id, int expired, int entire_expired, int length, int timestamp)
{
    if (gCtx.phoneUpdateTime.elapsed()/1000 > 70) {
        qDebug() << "c++: phone is not online - ";
        return;
    }
    if (gCtx.phoneSyncChannel.empty()) {
        qDebug() << "c++: phone sync channel is empty";
        return;
    }
    if (gCtx.phoneSyncChannel.size() != 64) {
        qDebug() << "c++: phone sync channel size is not correct - " << gCtx.phoneSyncChannel.size();
        return;
    }

    qDebug() << "c++: sync channelid - "
             << QString::fromStdString(gCtx.zebra_->hex_encode(gCtx.phoneSyncChannel));
    qDebug() << "c++: frin channelid - "
             << QString::fromStdString(gCtx.zebra_->hex_encode(friend_channel_id));
    qDebug() << "c++: sync message size - "
             << message.size() << " message id - " << message_id;

    gCtx.zebra_->send_sync_message(gCtx.phoneSyncChannel, friend_channel_id,
                                  type, message, expired, entire_expired, timestamp, length, message_id);
    qDebug() << "c++: send sync message to phone ok";
    return;
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
        const int baseType,
        const string &message,
        unsigned long message_id,
        int expired,
        int entire_expired,
        int length,
        int timestamp)
{
    qDebug() << _countMessage++
             << "********************friend_offline_message***********************" ;

    int type = baseType;
    int refreshBackColor = 0;


    /* 接收消息开关检查 */
    if (isReceiveEnable() == false) {
        return;
    }

    /* 特殊消息处理 */
    int ret = 0;
    ret = processPhoneCommand(type, message, friend_channel_id);
    if (ret < 0 || ret == 1) {
        return;
    }

    /* 消息声音开关使能 */
    if (isSoundEnable()) {
        Utils::playMessageSound();
    }

    /* 消息转发类型处理 */
    int messageDirection = 1;
    if (type > ImapiMessageType_ForwadSelfOffset) {
        type -= ImapiMessageType_ForwadSelfOffset;
        qDebug() << "c++: sync self messaage";
        messageDirection = 0;
    } else if (type > ImapiMessageType_ForwadOffset && type < ImapiMessageType_ForwadSelfOffset) {
        type -= ImapiMessageType_ForwadOffset;
        qDebug() << "c++: sync oppsite messaage";
    } else {
        forwardMessage(friend_channel_id, type + ImapiMessageType_ForwadOffset,
                       message, message_id, expired, entire_expired, length, timestamp);
    }

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList_.begin(); it != c->friendList_.end(); it++) {
        Friend &f = it.value();
        int idx = f.messageList.size();

        if (friend_channel_id == StringToHex(f.friendChannelId_.toStdString())) {
            Message *m        = new Message;
            m->data           = message;
            m->driect         = messageDirection;
            m->messageType    = MessageTypeNone;
            m->MessageMethord = MessageMethodOffline;
            m->voiceSeconds   = 0;

            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_offline_message", "receive one online message",
                 f.cacheIndex_, message.c_str());

           qDebug() << "c++: friend_online_message ---- type "<<type;
            /* 如果是当前界面显示的好友，那么添加到界面，否则不加 */
            if (c->currentUseId_ == f.cacheIndex_ && c->currentUseType_ == CHATITEM_TYPE_FRIEND) {
                f.messageUnreadCount_ = 0;
                refreshBackColor = 1;

                /* 判断类型 */
                switch (type) {
                case MessageTypeWord:
                    m->messageType = MessageTypeWord;
                    MessageWidget::addMessageToWidget(f.cacheIndex_, f.name_, type,
                                messageDirection, QString::fromStdString(m->data), idx); break;
                case MessageTypeImage:
                    m->messageType = MessageTypeImage;
                    qDebug() << "c++: friend_online_message ------------- cacheIndex_ "<<f.cacheIndex_;
                    MessageWidget::addImageToWidget(f.cacheIndex_, f.name_, type,
                                messageDirection, m->data, idx); break;
                case MessageTypeVoice:
                    m->messageType = MessageTypeVoice;
                    m->voiceSeconds = length;
                    MessageWidget::addVoiceToWidget(f.cacheIndex_, f.name_, type, messageDirection,
                                QString::fromStdString(m->data), length, idx); break;
                default:
                    break;
                }
            }
            f.messageUnreadCount_++;

            /* 判断类型 */
            switch (type) {
            case MessageTypeWord : m->messageType = MessageTypeWord ; break;
            case MessageTypeImage: m->messageType = MessageTypeImage; break;
            case MessageTypeVoice: m->messageType = MessageTypeVoice; m->voiceSeconds = length; break;
            default:
                break;
            }

            f.setTimeAndState(f.cacheIndex_, MessageMethodOffline);
            f.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_offline_message", "receive one online message",
                 f.cacheIndex_, message.c_str());

            /* 以下操作检查是否需要在chat页面显示好友 */
            int ret = c->atFirstPosition(f.cacheIndex_, CHATITEM_TYPE_FRIEND);
            if (ret == -1) {
                qDebug() << "c++: chatlist - add : " << f.cacheIndex_;
                c->insertOneChat(f.cacheIndex_, CHATITEM_TYPE_FRIEND, f.name_);
            } else if (ret == -2) {
                qDebug() << "c++: chatlist - move : " << f.cacheIndex_;
                c->removeOneChat(f.cacheIndex_, CHATITEM_TYPE_FRIEND);
                c->insertOneChat(f.cacheIndex_, CHATITEM_TYPE_FRIEND, f.name_);
            }
            Chat::displayChatNetState(f.cacheIndex_, MessageMethodOffline);
            if (refreshBackColor) {
                Utils::clearCurrentItemHighLight(c);
                Utils::setFriendItemHighLight(c, &f, f.cacheIndex_);
            } else {
                Chat::displayChatUnreadCount(f.cacheIndex_, f.messageUnreadCount_, CHATITEM_TYPE_FRIEND);
            }
        }
    }
    qDebug() << "\n";
    return;
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
        const int baseType,
        const string &message,
        unsigned long message_id,
        int expired,
        int entire_expired,
        int length,
        int timestamp)
{
    int type = baseType;
    int refreshBackColor = 0;

    qDebug() << _countMessage++
             << "********************friend_online_message***********************";

    /* 接收消息开关检查 */
    if (isReceiveEnable() == false) {
        return;
    }

    /* 特殊消息处理 */
    int ret = 0;
    ret = processPhoneCommand(type, message, friend_channel_id);
    if (ret < 0 || ret == 1) {
        return;
    }

    /* 消息转发类型检查 */
    int messageDirection = 1;
    if (type > ImapiMessageType_ForwadSelfOffset) {
        type -= ImapiMessageType_ForwadSelfOffset;
        qDebug() << "c++: sync self messaage";
        messageDirection = 0;
    } else if (type > ImapiMessageType_ForwadOffset && type < ImapiMessageType_ForwadSelfOffset) {
        type -= ImapiMessageType_ForwadOffset;
        qDebug() << "c++: sync opppsite messaage";
    } else {
        forwardMessage(friend_channel_id, type + ImapiMessageType_ForwadOffset,
            message, message_id, expired, entire_expired, length, timestamp);
    }

    /* 消息声音开关使能 */
    if (isSoundEnable()) {
        Utils::playMessageSound();
    }

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList_.begin(); it != c->friendList_.end(); it++) {
        Friend &f = it.value();
        int idx = f.messageList.size();
        if (friend_channel_id == StringToHex(f.friendChannelId_.toStdString())) {

            Message *m        = new Message;
            m->data           = message;
            m->driect         = messageDirection;
            m->messageType    = MessageTypeNone;
            m->MessageMethord = MessageMethodOnline;
            m->voiceSeconds   = 0;

            /* 如果是当前界面显示的好友，那么添加到界面，否则不加 */
            if (c->currentUseId_ == f.cacheIndex_ && c->currentUseType_ == CHATITEM_TYPE_FRIEND) {
                f.messageUnreadCount_ = 0;
                refreshBackColor = 1;

                qDebug() << "c++:  friend_online_message---- type "<<type;
                /* 判断类型 */
                switch (type) {
                case MessageTypeWord:
                    m->messageType = MessageTypeWord;
                    MessageWidget::addMessageToWidget(f.cacheIndex_, f.name_, type, messageDirection,
                                QString::fromStdString(m->data), idx); break;
                    qDebug()<<"c++  .............messageDirection is : "<<messageDirection;
                case MessageTypeImage:
                    m->messageType = MessageTypeImage;
                    MessageWidget::addImageToWidget(f.cacheIndex_, f.name_, type,
                                messageDirection, m->data, idx); break;
                case MessageTypeVoice:
                    m->messageType = MessageTypeVoice;
                    m->voiceSeconds = length;
                    MessageWidget::addVoiceToWidget(f.cacheIndex_, f.name_, type, messageDirection,
                                QString::fromStdString(m->data), length, idx); break;
                default:
                    break;
                }
            }
            f.messageUnreadCount_++;

            /* 判断类型 */
            switch (type) {
            case MessageTypeWord : m->messageType = MessageTypeWord ; break;
            case MessageTypeImage: m->messageType = MessageTypeImage; break;
            case MessageTypeVoice: m->messageType = MessageTypeVoice; m->voiceSeconds = length; break;
            default:
                break;
            }

            f.setTimeAndState(f.cacheIndex_, MessageMethodOnline);
            f.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "friend_online_message", "receive one online message",
                 f.cacheIndex_, message.c_str());

            /* 以下操作检查是否需要在chat页面显示好友 */
            int ret = c->atFirstPosition(f.cacheIndex_, CHATITEM_TYPE_FRIEND);
            if (ret == -1) {
                qDebug() << "c++: chatlist - add : " << f.cacheIndex_;
                c->insertOneChat(f.cacheIndex_, CHATITEM_TYPE_FRIEND, f.name_);
            } else if (ret == -2) {
                qDebug() << "c++: chatlist - move : " << f.cacheIndex_;
                c->removeOneChat(f.cacheIndex_, CHATITEM_TYPE_FRIEND);
                c->insertOneChat(f.cacheIndex_, CHATITEM_TYPE_FRIEND, f.name_);
            }
            Chat::displayChatNetState(f.cacheIndex_, MessageMethodOnline);
            if (refreshBackColor) {
                Utils::clearCurrentItemHighLight(c);
                Utils::setFriendItemHighLight(c, &f, f.cacheIndex_);
            } else {
                Chat::displayChatUnreadCount(f.cacheIndex_, f.messageUnreadCount_, CHATITEM_TYPE_FRIEND);
            }
        }
    }
    qDebug() << "\n";
    return;
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
        const string &friend_channel_id)
{
    if (gCtx.phoneQrChannel == qr_channel_id) {
        qDebug() << "c++: is not sync channel id";
        g_io_service.Send([friend_channel_id](){
            Utils::ShadowTalkSleep(500);
            int ret = gCtx.zebra_->handle_friend_request(friend_channel_id, true);
            std::cout << "c++: add friend result: " << ret << std::endl;
        });

        if (gCtx.phoneSyncChannel.empty()) {
            gCtx.phoneSyncChannel = friend_channel_id;
            qDebug() << "c++: sync-channelid : "
                     << QString::fromStdString(gCtx.zebra_->hex_encode(friend_channel_id));
        }
    } else {
        if (!gCtx.phoneSyncChannel.empty()) {
            g_io_service.Send([friend_channel_id](){
                std::string message = "friend_request";
                gCtx.zebra_->send_sync_message(gCtx.phoneSyncChannel, friend_channel_id,
                    ImapiMessageType_AddFriendRequest + ImapiMessageType_ForwadOffset,
                    message, 60, 3600, QDateTime::currentMSecsSinceEpoch()/1000,
                    message.size(), 0);
                std::cout << "c++: sync add friend request: " << std::endl;
            });
        }
    }
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
        const string &friend_channel_id, bool accepted)
{
    qDebug() << "c++: friend_request_reply - " << accepted;
    return;
}

/**
 *  功能描述: 已被对方通知删除好友
 *  @param friend_channel_id 好友通道id
 *
 *  @return 无
 */
void zebraDeleagates::friend_deleted(const string &friend_channel_id)
{
    std::cout << "c++: friend_deleted" << std::endl;
    if (!gCtx.phoneSyncChannel.empty()) {
        g_io_service.Send([friend_channel_id](){
            std::string message = "friend_request";
            gCtx.zebra_->send_sync_message(gCtx.phoneSyncChannel, friend_channel_id,
                ImapiMessageType_DeleteFriend + ImapiMessageType_ForwadOffset,
                message, 60, 3600, QDateTime::currentMSecsSinceEpoch()/1000,
                message.size(), 0);
            std::cout << "c++: sync delete friend request: " << std::endl;
        });
    }
    return;
}

/**
 *  功能描述: 存储数据操作
 *  @param key_id     key索引
 *  @param read_data  key数值
 *
 *  @return 无
 */
void zebraDeleagates::store_data(const string &key_id, const string &read_data)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList_.find(key_id);
    if (it != c->keyValueList_.end()) {
        it->second = read_data;
        return;
    } else {
        c->keyValueList_.insert(std::pair<std::string, std::string>(key_id, read_data));
    }
    return;
}

/**
 *  功能描述: 存储数据读取
 *  @param key_id     key索引
 *  @param read_data  key数值
 *
 *  @return 无
 */
void zebraDeleagates::read_data(const string &key_id, string &read_data)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList_.find(key_id);
    if (it != c->keyValueList_.end()) {
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
void zebraDeleagates::delete_data(const string &key_id)
{
    int deleteFlag = 0;
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    std::map<std::string, std::string>::iterator it;
    it = c->keyValueList_.find(key_id);
    if (it != c->keyValueList_.end()) {
        deleteFlag = 1;
    }
    c->keyValueList_.erase(key_id);
    return;
}

/**
 *  功能描述: 去重函数
 *  @param item    去重数值
 *  @param expire  超期时间
 *
 *  @return 无
 */


QMutex existLock;
std::set<std::string> existSet;

bool zebraDeleagates::isExisted(const string &item, unsigned int expire)
{
    existLock.lock();
    std::set<std::string>::iterator it;
    it = existSet.find(item);
    if (it != existSet.end()) {
        existLock.unlock();
        std::cout << "### c++: isExisted - exist message" << gCtx.zebra_->hex_encode(item) << std::endl;
        return true;
    } else {
        std::cout << "### c++: isExisted - new message" << gCtx.zebra_->hex_encode(item) << std::endl;
        existSet.insert(item);
        existLock.unlock();
        return false;
    }
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
        unsigned long message_id, int ret_code)
{
    qDebug() << "c++: handler_write_message_reply - " << message_id << " " << ret_code;
    return;
}


/**
 *  功能描述: ice 通道状态 非0为异常
 *  @param channel_id  通道索引
 *  @param state       ice状态
 *  @param ret_code    处理结果
 *
 *  @return 无
 */
void zebraDeleagates::ice_session_state(const std::string &channel_id, int state)
{
    return;
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
    std::cout << "c++: send_message_via_direct_connection" << std::endl;
    return -1;
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
    std::cout << "c++: bind_friend_channel" << std::endl;
    return;
}


/**
 *  功能描述: 接收到组的邀请
 *  @param group_channel_id    组id
 *  @param friend_channel_id   好友id
 *  @param 用户在组中的名字
 *
 *  @return 无
 */
void zebraDeleagates::group_chat_invite_received(
        const std::string &friend_channel_id,
        const std::string &group_channel_id,
        const std::string &my_name)
{
    std::cout << "c++: group_chat_invite_received" << std::endl;

    if (gCtx.zebra_) {
        gCtx.zebra_->sync_group_chat_invite_received(gCtx.phoneSyncChannel,
             friend_channel_id, group_channel_id, my_name);
    }
    return;
}


/**
 *  功能描述: 接受组的邀请的回调
 *  @param group_channel_id    组id
 *  @param friend_channel_id   好友id
 *  @param accepted            是否接受组邀请
 *  @param friend_member_id    成员id
 *
 *  @return 无
 */
void zebraDeleagates::group_chat_invite_reply_received(
        const std::string &friend_channel_id,
        const std::string &group_channel_id,
        bool accepted,
        const std::string &friend_member_id)
{
    std::cout << "group_chat_invite_reply_received" << std::endl;

    if (gCtx.zebra_) {
        gCtx.zebra_->sync_group_chat_invite_reply_received(gCtx.phoneSyncChannel,
             friend_channel_id, group_channel_id, accepted, friend_member_id);
    }
    return;
}

/**
 *  功能描述: 组新成员信息回调
 *  @param group_channel_id    组id
 *  @param friend_channel_id   好友id
 *  @param member_id           成员id
 *  @param name                成员名字
 *  @param join_time           成员加入的时间
 *
 *  @return 无
 */
void zebraDeleagates::group_chat_member(
        const string &group_channel_id,
        const string &member_id,
        const std::string &name,
        unsigned long join_time)
{
    std::cout << "c++: group_chat_member" << std::endl;
    if (gCtx.zebra_) {
        gCtx.zebra_->sync_group_chat_member(gCtx.phoneSyncChannel,
             group_channel_id, member_id, name, join_time);
    }
    return;
}


/**
 *  功能描述: 组内移除了一个成员回调
 *  @param group_channel_id    组id
 *  @param remover             删除的好友名字
 *  @param member_id           成员id
 *  @param join_time           成员加入的时间
 *  @param removed_time        删除的时间
 *
 *  @return 无
 */
void zebraDeleagates::group_chat_member_removed(
        const string &group_channel_id,
        const std::string &remover,
        const string &member_id,
        unsigned long removed_time)
{
    std::cout << "c++: group_chat_member_removed" << std::endl;
    if (gCtx.zebra_) {
        gCtx.zebra_->sync_group_chat_member_removed(gCtx.phoneSyncChannel,
             group_channel_id, remover, member_id, removed_time);
    }
    return;
}


/**
 *  功能描述: 接收组消息
 *  @param group_channel_id    组id
 *  @param author              删除的好友名字
 *  @param type                消息类型
 *  @param message             消息内容
 *  @param message_id          消息id
 *  @param expired             过期时间
 *  @param entire_expired      整理过期时间
 *  @param length              消息长度
 *  @param timestamp           时间戳
 *  @param author_name         发消息人的名称
 *  @return 无
 */
void zebraDeleagates::group_chat_message_received(
        const string &group_channel_id,
        const string &author,
        const int type,
        const string &message,
        unsigned long message_id,
        int expired,
        int entire_expired,
        int length,
        int timestamp,
        const std::string &author_name)
{
    qDebug() << _countMessage++
             << "********************group_chat_message_received***********************";
    int messageDirection = 1;
    int refreshBackColor = 0;

    /* 接收消息开关检查 */
    if (isReceiveEnable() == false) {
        return;
    }

    /* 消息声音开关使能 */
    if (isSoundEnable()) {
        Utils::playMessageSound();
    }

    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }
    int type_ = type;

    /* 同步组消息 */
    qDebug() << "c++: group type - " << type_;
    if (type_ < ImapiMessageType_ForwadGOffset) {
        if (gCtx.zebra_) {
            gCtx.zebra_->sync_group_chat_message_received(gCtx.phoneSyncChannel,
                 group_channel_id, author, type_ + ImapiMessageType_ForwadGOffset, message, message_id, expired,
                 entire_expired, length, timestamp, author_name);
        }
    }
    if (type_ > ImapiMessageType_ForwadGOffset && type_ < ImapiMessageType_ForwadGSelfOffset) {
        type_ -= ImapiMessageType_ForwadGOffset;
    }
    if (type_ > ImapiMessageType_ForwadGSelfOffset) {
        type_ -= ImapiMessageType_ForwadGSelfOffset;
        messageDirection = 0;
    }

    QMap<int, Group>::iterator it;
    for (it = c->groupList_.begin(); it != c->groupList_.end(); it++) {
        Group &g = it.value();
        int idx = g.messageList_.size();
        if (group_channel_id == StringToHex(g.groupChannelId_.toStdString())) {

            GroupMessage *m   = new GroupMessage;
            m->data           = message;
            m->driect         = messageDirection;
            m->messageType    = MessageTypeNone;
            m->MessageMethord = MessageMethodOffline;
            m->voiceSeconds   = 0;
            m->senderName     = author_name;

            /* 如果是当前界面显示的好友，那么添加到界面，否则不加 */
            if (c->currentUseId_ == g.cacheIndex_ && c->currentUseType_ == CHATITEM_TYPE_GROUP)
            {
                g.messageUnreadCount_ = 0;
                switch (type_) {
                case MessageTypeWord:
                    m->messageType = MessageTypeWord;
                    MessageWidget::addMessageToWidget(g.cacheIndex_, QString::fromStdString(author_name),
                        type_, messageDirection, QString::fromStdString(m->data),idx); break;
                case MessageTypeImage:
                    m->messageType = MessageTypeImage;
                    MessageWidget::addImageToWidget(g.cacheIndex_, QString::fromStdString(author_name),
                        type_, messageDirection, m->data, idx); break;
                case MessageTypeVoice:
                    m->messageType = MessageTypeVoice;
                    m->voiceSeconds = length;
                    MessageWidget::addVoiceToWidget(g.cacheIndex_, QString::fromStdString(author_name),
                        type_, messageDirection, QString::fromStdString(m->data), length, idx); break;
                default:
                    break;
                }
            } else {
                if (messageDirection == 0) {
                    g.messageUnreadCount_++;
                }
            }


            /* 判断类型 */
            switch (type_) {
            case MessageTypeWord : m->messageType = MessageTypeWord ; break;
            case MessageTypeImage: m->messageType = MessageTypeImage; break;
            case MessageTypeVoice: m->messageType = MessageTypeVoice; m->voiceSeconds = length; break;
            default:
                break;
            }

            g.insertOneMessage(m);
            slog("func<%s> : msg<%s> para<UserIndex - %d, Message - %s>\n",
                 "group_chat_message_received", "receive one group message",
                 g.cacheIndex_, message.c_str());

            /* 以下操作检查是否需要在chat页面显示好友 */
            int ret = c->atFirstPosition(g.cacheIndex_, CHATITEM_TYPE_GROUP);
            if (ret == -1) {
                qDebug() << "c++: add new one to chatlist";
                c->insertOneChat(g.cacheIndex_, CHATITEM_TYPE_GROUP, g.gourpName_);
            } else if (ret == -2) {
                qDebug() << "c++: move one to first position";
                c->removeOneChat(g.cacheIndex_, CHATITEM_TYPE_GROUP);
                c->insertOneChat(g.cacheIndex_, CHATITEM_TYPE_GROUP, g.gourpName_);
            }

            if (refreshBackColor) {
                Utils::clearCurrentItemHighLight(c);
                Utils::setGroupItemHighLight(c, &g, g.cacheIndex_);
            } else {
                Chat::displayChatUnreadCount(g.cacheIndex_, g.messageUnreadCount_, CHATITEM_TYPE_GROUP);
            }
        }
    }
    qDebug() << "\n";
    return;
}

/**
 *  功能描述: 组的channel改变
 *  @param group_channel_id    组channelid
 *  @param channel_name        channel名称
 *  @param changed_time        修改的时间
 *  @return 无
 */
void zebraDeleagates::group_channel_name_changed(
        const string &group_channel_id,
        const string &channel_name,
        unsigned long changed_time)
{
    std::cout << "c++: group_channel_name_changed" << std::endl;
    if (gCtx.zebra_) {
        gCtx.zebra_->sync_group_channel_name_changed(gCtx.phoneSyncChannel,
             group_channel_id, channel_name, changed_time);
    }
    return;
}

/**
 *  功能描述: 发送完文件数据后，回调传送接口
 *  @param result    传送结果
 *  @param fileid        文件的id
 *  @param channel_id        发送的好友id
 *  @return 无
 */

int zebraDeleagates::send_file_result(
        const int result,
        unsigned long fileid,
        const string &channel_id){
    qDebug("c++: zebraDeleagates::send_file_result");
    if (result!=0){
      qDebug()<<"c++ zebraDeleagates::send_file_result:send file failed.";
    }

    return 0;
}
int zebraDeleagates::recv_file_result(
        const int result,
        const string &channel_id,
        const string &digest){
   qDebug()<<"c++: zebraDeleagates::recv_file_result: beginning....";
   if (result!=0){
        qDebug()<<"c++: zebraDeleagates::recv_file_result recv file failed.";
        return -1;
   }
   std::cout << "digest:" << digest <<std::endl;
   qDebug() << "result:" << result;
   if (digest=="send_contact_file" && result==0){
      qDebug()<<"c++: zebraDeleagates::recv_file_result recv contact_file.";
      //通知开始读取文件
      int ret = 0;
      ret=processPhoneCommandEX(MessagetypePCBackup,"", channel_id);
      return 0;
   }
   return 0;
}

int zebraDeleagates::handle_file_digest(
        const string &channel_id,
        const string &digest,
        string &path)
{
    if (digest=="send_contact_file"){
      //联系人列表自动接收；并制定路径
      path=SHADOW_SYNC_FILE;
      //通知接收文件并显示到聊天的界面
      return 0;
    }
    else
    {
      QString tagpath= QCoreApplication::applicationDirPath()+"/temp";
      path=tagpath.toStdString();
    }
    return 0;
}
//offset 已完成传输数据
int zebraDeleagates::handle_send_file_process(
        const string &channel_id,
        unsigned long fileid,
        long offset)
{
   //offset 给聊天界面显示传输进度；单位：字节
   //需要在聊天的页面做一个显示接收的进度条
   //在聊天的页面做一个自动接收
    return 0;
}

int zebraDeleagates::handle_recv_file_process(
        const string &channel_id,
        const string &digest,
        long offset)
{

    return 0;
}
