/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_cache.cpp
 *  简要描述: 缓存接口
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include <QMap>
#include <map>
#include <string>
#include "st_cache.h"
#include "st_friend.h"
#include "st_context.h"
#include "st_chat.h"

Cache::Cache(): friendCount_(0), groupCount_(0), currentUseId_(-1), currentUseType_(-1) {}
Cache::~Cache() {}

/***************************  联系人操作接口  ************************************/

/**
 *  功能描述: 获取下一个加入缓存的结构id
 *  @param 无
 *
 *  @return 无
 */
int Cache::getNextIndex()
{
    return this->getFriendCount();
}

/**
 *  功能描述: 获取好友结构数量
 *  @param  无
 *
 *  @return 无
 */
int Cache::getFriendCount()
{
    return friendList_.size();
}

/**
 *  功能描述: 获取界面当前好友结构id
 *  @param index  好友id
 *
 *  @return 无
 */
void Cache::setCurrentId(int id, int type, QString name)
{
    this->currentUseId_   = id;
    this->currentUseType_ = type;
    this->currentUseName_ = name;
    return;
}

/**
 *  功能描述: 按id获取一个好友结构指针
 *  @param index  好友索引
 *
 *  @return 无
 */
Friend *Cache::getOneFriend(int index)
{
    QMap<int, Friend>::iterator it;
    for(it = friendList_.begin(); it != friendList_.end(); it++) {
        Friend &f = it.value();
        if (f.cacheIndex == index) {
            return &(it.value());
        }
    }
    return nullptr;
}

/**
 *  功能描述: 检查好友是否已经存在于缓存
 *  @param friendChannelId 好友channelid
 *
 *  @return 无
 */
bool Cache::isExistFriend(QString friendChannelId)
{
    QMap<int, Friend>::iterator it;
    for(it = friendList_.begin(); it != friendList_.end(); it++) {
        Friend &f = it.value();
        if (f.friendChannelId.compare(friendChannelId) == 0) {
            return true;
        }
    }
    return false;
}

/**
 *  功能描述: 将一个好友结构加入缓存
 *  @param newFriend   好友信息结构指针
 *
 *  @return 无
 */
void Cache::insertOneFriend(Friend *newFriend)
{
    friendList_.insert(this->friendCount_, *newFriend);
    this->friendCount_++;
    delete newFriend;
    return;
}

/******************************  缓存中channel操作接口 ***********************************/

/**
 *  功能描述: 获取channel信息结构
 *  @param  channel  channel索引
 *
 *  @return 成功 返回结构指针   失败 返回nullptr
 */
struct LocalChannel *Cache::getChannel(QString channelId)
{
    QMap<QString, struct LocalChannel *>::iterator it;
    it = this->channelList_.find(channelId);
    if (it == this->channelList_.end()) {
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
void Cache::insertChannel(struct LocalChannel *channel)
{
    this->channelList_.insert(channel->channelId, channel);
}

/**
 *  功能描述: 从映射表删除channel信息
 *  @param channelId channel索引
 *
 *  @return 无
 */
void Cache::deleteChannel(QString channeldId)
{
    struct LocalChannel *c = nullptr;
    c = getChannel(channeldId);
    this->channelList_.remove(channeldId);
    delete c;
    return;
}

/**
 *  功能描述: 检查缓存中是否已经存在此channel
 *  @param channelId channel索引
 *
 *  @return 存在返回true 不存在返回false
 */
bool Cache::isExistChannel(QString channelId)
{
    struct LocalChannel *c = nullptr;
    c = getChannel(channelId);
    if (c == NULL) {
        return false;
    }
    return true;
}

/******************************  缓存中key与value接口 ***********************************/

/**
 *  功能描述: 获取key,value对
 *  @param key    密钥索引
 *
 *  @return 成功 返回value   失败 返回空字符串
 */
std::string Cache::getKeyValue(std::string key)
{
    std::map<std::string, std::string>::iterator it;
    it = this->keyValueList_.find(key);
    if (it == this->keyValueList_.end()) {
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
void Cache::insertKeyValue(std::string key, std::string value)
{
    this->keyValueList_.insert(pair<std::string, std::string>(key, value));
}

/**
 *  功能描述: 删除key,value对
 *  @param key   密钥索引
 *
 *  @return 无
 */
void Cache::deleteKeyValue(std::string key)
{
    this->keyValueList_.erase(key);
}

/**
 *  功能描述: 检查缓存中是否已经存在key与value
 *  @param key key值
 *
 *  @return 存在返回true 不存在返回false
 */
bool Cache::isExistChannel(std::string key)
{
    std::string retStr = getKeyValue(key);
    if (retStr.empty()) {
        return false;
    }
    return true;
}

/**
 *  功能描述: 清理缓存
 *  @param  无
 *
 *  @return 无
 */
void Cache::CleanCache()
{
    friendCount_ = currentUseId_ = 0;
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
void Cache::cleanFriend()
{
    this->friendList_.clear();
}


/******************************  chatList ***********************************/

/**
 *  功能描述: 插入chatlist列表
 *  @param cacheIndex  缓存索引
 *  @param type        节点类型 组或者联系人
 *  @param friendName  节点名称，组名或者联系人名
 *
 *  @return 无
 */
void Cache::insertOneChat(int cacheIndex, int type, QString friendName)
{
    int idx = 0;
    QString shortName;

    ChatItem *item = new ChatItem();
    if (item == NULL) {
        return;
    }

    QList<ChatItem *>::iterator it;
    for(it = chatList_.begin(); it != chatList_.end(); it++) {
        Chat::updateListIndexForChat(idx, idx + 1);
        idx++;
    }

    item->cacheIndex = cacheIndex;
    item->type = type;

    chatList_.insert(chatList_.begin(), item);

    if (type == CHATITEM_TYPE_FRIEND) {
        shortName = "Friend";
    } else {
        shortName = "Group";
    }
    Chat::addFrientToChat(friendName, shortName, cacheIndex, 0);
    return;
}


/**
 *  功能描述: 从chatlist列表中删除元素
 *  @param cacheIndex  缓存索引
 *  @param type        节点类型 组或者联系人
 *
 *  @return 无
 */
void Cache::removeOneChat(int cacheIndex, int type)
{
    int chatIdx = 0;
    int flag = 0;

    QList<ChatItem *>::iterator it;
    for(it = chatList_.begin(); it != chatList_.end(); it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == cacheIndex && item->type == type) {
                flag = 1;
                break;
            }
            chatIdx++;
        }
    }
    if (flag == 1) {
        chatList_.erase(it);
        delete *it;
        Chat::removeFrientFromChat(chatIdx);
        qDebug() << "c++: remove chatIdx - " << chatIdx;
        return;
    }
    qDebug() << "c++: remove chat widget fail : cacheIdx - " << cacheIndex << " type - " << type;
    return;
}

/**
 *  功能描述: 检查chatlist成员的位置，检查是否存在此成员
 *  @param cacheIndex  缓存索引
 *  @param type        节点类型 组或者联系人
 *
 *  @return 无
 */
int Cache::atFirstPosition(int cacheIndex, int type)
{
    int result = 0;
    int idx = 0;

    QList<ChatItem *>::iterator it;
    for(it = chatList_.begin(); it != chatList_.end();it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == cacheIndex && item->type == type) {
                result = 1;
                break;
            }
            idx++;
        }
    }
    /* 有结果，并且已经在第一个位置上 */
    if (result == 1 && idx == 0) {
        return 0;
    }
    /* 有结果，但是不在第一个位置上 */
    if (result == 1 && idx != 0) {
        return -2;
    }
    /* 没有找到 */
    return -1;
}

/**
 *  功能描述: 获取当前显示项在chat listview中的位置
 *  @param cacheIndex  缓存索引
 *  @param type        节点类型 组或者联系人
 *
 *  @return 返回位置编号
 */
int Cache::getPositionNum(int cacheIndex, int type)
{
    int idx = 0;
    int result = 0;

    QList<ChatItem *>::iterator it;
    for(it = chatList_.begin(); it != chatList_.end();it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == cacheIndex && item->type == type) {
                result = 1;
                break;
            }
            idx++;
        }
    }
    if (result == 1) {
        return idx;
    } else {
        return -1;
    }
}

/**
 *  功能描述: 清理通道缓存
 *  @param  无
 *
 *  @return 无
 */
void Cache::cleanChannel()
{
    QMap<QString, struct LocalChannel *>::iterator it;
    for (it = this->channelList_.begin(); it != this->channelList_.end(); it++) {
        delete it.value();
    }
    this->channelList_.clear();
    return;
}

/**
 *  功能描述: 清理key缓存
 *  @param  无
 *
 *  @return 无
 */
void Cache::cleanKeyValue()
{
    this->keyValueList_.clear();
}

/*********************************  组操作接口  *****************************************/

/**
 *  功能描述: 将一个组结构加入缓存
 *  @param newGroup   组信息结构指针
 *
 *  @return 无
 */
void Cache::insertOneGroup(Group *newGroup)
{
    groupList_.insert(this->groupCount_, *newGroup);
    this->groupCount_++;
    delete newGroup;
    return;
}

/**
 *  功能描述: 获取组结构数量
 *  @param  无
 *
 *  @return 无
 */
int Cache::getGroupCount()
{
    return groupList_.size();
}

/**
 *  功能描述: 获取下一个加入缓存的结构id
 *  @param 无
 *
 *  @return 无
 */
int Cache::getNextGroupIndex()
{
    return this->getGroupCount();
}

/**
 *  功能描述: 根据缓存中的索引获取组结构的指针
 *  @param cacheIndex  组在缓存中的索引编号
 *
 *  @return 成功返回Group指针  失败返回空
 */
Group *Cache::getOneGroup(int cacheIndex)
{
    QMap<int, Group>::iterator it;
    for(it = groupList_.begin(); it != groupList_.end(); it++) {
        Group &g = it.value();
        if (g.gid_ == cacheIndex) {
            return &(it.value());
        }
    }
    return nullptr;
}

/**
 *  功能描述: 根据组的channelId获取组的指针
 *  @param cacheIndex  组在缓存中的索引编号
 *
 *  @return 成功返回Group指针  失败返回空
 */
Group *Cache::getOneGroup(QString groupChannelId)
{
    QMap<int, Group>::iterator it;
    for(it = groupList_.begin(); it != groupList_.end(); it++) {
        Group &g = it.value();
        if (g.groupChannelId_ == groupChannelId) {
            return &(it.value());
        }
    }
    return nullptr;
}

/**
 *  功能描述: 检查好友是否已经存在于缓存
 *  @param groupChannelId 组在缓存中的索引编号
 *
 *  @return 存在返回true  不存在返回false
 */
bool Cache::isExistGroup(QString groupChannelId)
{
    QMap<int, Group>::iterator it;
    for(it = groupList_.begin(); it != groupList_.end(); it++) {
        Group &g = it.value();
        if (g.groupChannelId_.compare(groupChannelId) == 0) {
            return true;
        }
    }
    return false;
}

/**
 *  功能描述: 清理组缓存
 *  @param 无
 *
 *  @return 无
 */
void Cache::cleanGroup()
{
    this->groupList_.clear();
}
