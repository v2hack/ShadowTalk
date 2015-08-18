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
#include <QMap>

#include "st_cache.h"
#include "st_friend.h"
#include "st_context.h"

Cache::Cache(): friendCount(0), currentUseFriendId(-1) {
}
Cache::~Cache() {
}

/**
 *  功能描述: 获取下一个加入缓存的结构id
 *  @param 无
 *
 *  @return 无
 */
int Cache::getNextIndex() {
    return this->getFriendCount() + 1;
}

/**
 *  功能描述: 获取好友结构数量
 *  @param  无
 *
 *  @return 无
 */
int Cache::getFriendCount() {
    return friendList.size();
}

/**
 *  功能描述: 获取界面当前好友结构id
 *  @param index  好友id
 *
 *  @return 无
 */
void Cache::setCurrentFriendId(int id) {
    this->currentUseFriendId = id;
}

/**
 *  功能描述: 按id获取一个好友结构指针
 *  @param index  好友索引
 *
 *  @return 无
 */
Friend *Cache::getOneFriend(int index) {
    QMap<int, Friend>::iterator it = friendList.find(index);
    if (it == friendList.end()) {
        return nullptr;
    }
    return &(*it);
}

/**
 *  功能描述: 将一个好友结构加入缓存
 *  @param newFriend   好友信息结构指针
 *
 *  @return 无
 */
void Cache::insertOneFriend(Friend *newFriend) {
    this->friendCount++;
    friendList.insert(this->friendCount, *newFriend);
    return;
}

/**
 *  功能描述: 获取channel信息结构
 *  @param  channel  channel索引
 *
 *  @return 成功 返回结构指针   失败 返回nullptr
 */
struct LocalChannel *Cache::getChannel(QString channelId){
    QMap<QString, struct LocalChannel *>::iterator it;
    it = this->channelList.find(channelId);
    if (it == this->channelList.end()) {
        return nullptr;
    }
    return it.value();
}

/**
 *  功能描述: 插入channel信息到列表
 *  @param channel   channel信息结构指针
 *
 *  @return 无
 */
void Cache::insertChannel(struct LocalChannel *channel) {
    this->channelList.insert(channel->channelId, channel);
}


/**
 *  功能描述: 从映射表删除channel信息
 *  @param channelId channel索引
 *
 *  @return 无
 */
void Cache::deleteChannel(QString channeldId) {
    struct LocalChannel *c = nullptr;
    c = getChannel(channeldId);
    this->channelList.remove(channeldId);
    delete c;
}

/**
 *  功能描述: 获取key,value对
 *  @param key    密钥索引
 *
 *  @return 成功 返回键值对指针   失败 返回nullptr
 */
QString Cache::getKeyValue(QString key) {
    QMap<QString, QString>::iterator it;
    it = this->keyValueList.find(key);
    if (it == this->keyValueList.end()) {
        return "";
    }
    return it.value();
}


/**
 *  功能描述: 插入key,value对
 *  @param key    密钥索引
 *  @param value  密钥字符串
 *
 *  @return 无
 */
void Cache::insertKeyValue(QString key, QString value){
    this->keyValueList.insert(key, value);
}


/**
 *  功能描述: 删除key,value对
 *  @param key   密钥索引
 *
 *  @return 无
 */
void Cache::deleteKeyValue(QString key) {
    this->keyValueList.remove(key);
}














