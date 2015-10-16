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

#include <map>
#include <string>

#include "st_cache.h"
#include "st_friend.h"
#include "st_context.h"
#include "st_chat.h"

Cache::Cache(): friendCount(0), groupCount(0), currentUseId(-1) {
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
    return this->getFriendCount();
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
void Cache::setCurrentId(int id, int type, QString name) {
    this->currentUseId = id;
    this->currentUseType = type;
    this->currentUseName = name;
}

/**
 *  功能描述: 按id获取一个好友结构指针
 *  @param index  好友索引
 *
 *  @return 无
 */
Friend *Cache::getOneFriend(int index) {
    QMap<int, Friend>::iterator it;
    for(it = friendList.begin(); it != friendList.end(); it++) {
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
bool Cache::isExistFriend(QString friendChannelId) {
    QMap<int, Friend>::iterator it;
    for(it = friendList.begin(); it != friendList.end(); it++) {
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
void Cache::insertOneFriend(Friend *newFriend) {
    friendList.insert(this->friendCount, *newFriend);
    this->friendCount++;
    delete newFriend;
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


bool Cache::isExistChannel(QString channelId) {
    struct LocalChannel *c = nullptr;
    c = getChannel(channelId);
    if (c == NULL) {
        return false;
    }
    return true;
}


/**
 *  功能描述: 获取key,value对
 *  @param key    密钥索引
 *
 *  @return 成功 返回键值对指针   失败 返回nullptr
 */
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

bool Cache::isExistChannel(std::string key) {
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
void Cache::CleanCache() {
    friendCount = currentUseId = 0;
    qDebug() << "clean friends";
    cleanFriend();
    qDebug() << "clean channels";
    cleanChannel();
    qDebug() << "clean key-value";
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
    this->friendList.clear();
}



/******************************  chatList *************************************************/

/**
 *  功能描述: 插入chatlist列表
 *  @param friendListId  friendList中的序号
 *  @param friendName    好友名字
 *
 *  @return 无
 */
void Cache::insertOneChat(int cacheIndex, int type, QString friendName) {
    int idx = 0;
    QString shortName;

    ChatItem *item = new ChatItem();
    if (item == NULL) {
        return;
    }

    QList<ChatItem *>::iterator it;
    for(it = chatList.begin(); it != chatList.end(); it++) {
        updateListIndexForChat(idx, idx + 1);
        idx++;
    }

    item->cacheIndex = cacheIndex;
    item->type = type;

    chatList.insert(chatList.begin(), item);

    if (type == CHATITEM_TYPE_FRIEND) {
        shortName = "Group";
    } else {
        shortName = "Friend";
    }
    addFrientToChat(friendName, shortName, cacheIndex, 0);
    return;
}


/**
 *  功能描述: 从chatlist列表中删除元素
 *  @param friendListId  friendList中的序号
 *
 *  @return 无
 */
void Cache::removeOneChat(int cacheIndex, int type) {
    int chatIdx = 0;

    QList<ChatItem *>::iterator it;
    for(it = chatList.begin(); it != chatList.end(); it++) {
        ChatItem *item = *it;
        if (item) {
            if (item->cacheIndex == cacheIndex && item->type == type) {
                break;
            }
            chatIdx++;
        }
    }
    if (chatIdx != -1) {
        chatList.erase(it);
        delete *it;
        removeFrientFromChat(chatIdx);
    }
    return;
}

/**
 *  功能描述: 检查chatlist成员的位置，检查是否存在此成员
 *  @param friendListId  friendList中的序号
 *
 *  @return 无
 */
int Cache::atFirstPosition(int cacheIndex, int type) {
    int result = 0;
    int idx = 0;

    QList<ChatItem *>::iterator it;
    for(it = chatList.begin(); it != chatList.end();it++) {
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


//int Cache::getFriendIdOfChat(int chatId) {
//    if (chatId > chatList.size()) {
//        return -1;
//    }
//    return chatList.at(chatId);
//}


int Cache::getPositionNum(int cacheIndex, int type) {
    int idx = 0;
    int result = 0;

    QList<ChatItem *>::iterator it;
    for(it = chatList.begin(); it != chatList.end();it++) {
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


/*********************************  组操作接口  *****************************************/

/**
 *  功能描述: 将一个组结构加入缓存
 *  @param newGroup   组信息结构指针
 *
 *  @return 无
 */
void Cache::insertOneGroup(Group *newGroup) {
    groupList.insert(this->groupCount, *newGroup);
    this->groupCount++;
    delete newGroup;
    return;
}

/**
 *  功能描述: 获取组结构数量
 *  @param  无
 *
 *  @return 无
 */
int Cache::getGroupCount() {
    return groupList.size();
}

/**
 *  功能描述: 获取下一个加入缓存的结构id
 *  @param 无
 *
 *  @return 无
 */
int Cache::getNextGroupIndex() {
    return this->getGroupCount();
}

Group *Cache::getOneGroup(int index) {
    QMap<int, Group>::iterator it;
    for(it = groupList.begin(); it != groupList.end(); it++) {
        Group &g = it.value();
        if (g.gid_ == index) {
            return &(it.value());
        }
    }
    return nullptr;
}

Group *Cache::getOneGroup(QString groupChannelId) {
    QMap<int, Group>::iterator it;
    for(it = groupList.begin(); it != groupList.end(); it++) {
        Group &g = it.value();
        if (g.groupChannelId_ == groupChannelId) {
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
bool Cache::isExistGroup(QString groupChannelId) {
    QMap<int, Group>::iterator it;
    for(it = groupList.begin(); it != groupList.end(); it++) {
        Group &g = it.value();
        if (g.groupChannelId_.compare(groupChannelId) == 0) {
            return true;
        }
    }
    return false;
}

void Cache::cleanGroup(){
    this->groupList.clear();
}
