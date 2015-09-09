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


#include <map>
#include <string>

std::string Cache::getKeyValue(std::string key) {
    std::map<std::string, std::string>::iterator it;
    it = this->keyValueList.find(key);
    if (it == this->keyValueList.end()) {
        return "";
    }
    return it->second;
}


/**
 *  功能描述: 插入key,value对
 *  @param key    密钥索引
 *  @param value  密钥字符串
 *
 *  @return 无
 */
void Cache::insertKeyValue(std::string key, std::string value){
    this->keyValueList.insert(pair<std::string, std::string>(key, value));
}

/**
 *  功能描述: 删除key,value对
 *  @param key   密钥索引
 *
 *  @return 无
 */
void Cache::deleteKeyValue(std::string key) {
    this->keyValueList.erase(key);
}

/**
 *  功能描述: 清理缓存
 *  @param  无
 *
 *  @return 无
 */
void Cache::CleanCache() {
    friendCount = currentUseFriendId = 0;
    cleanFriend();
    cleanChannel();
    cleanKeyValue();
    return;
}

/**
 *  功能描述: 清理好友缓存
 *  @param  无
 *
 *  @return 无
 */
void Cache::cleanFriend() {
    QMap<int, Friend>::iterator it;
    for (it = this->friendList.begin(); it != this->friendList.end(); it++) {
        Friend *f = &(it.value());
        delete f;
    }
    this->friendList.clear();
}

/**
 *  功能描述: 清理通道缓存
 *  @param  无
 *
 *  @return 无
 */
void Cache::cleanChannel() {
    QMap<QString, struct LocalChannel *>::iterator it;
    for (it = this->channelList.begin(); it != this->channelList.end(); it++) {
        delete it.value();
    }
    this->channelList.clear();
}

/**
 *  功能描述: 清理key缓存
 *  @param  无
 *
 *  @return 无
 */
void Cache::cleanKeyValue() {
    this->keyValueList.clear();
}
