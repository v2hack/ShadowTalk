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

#include "cache.h"
#include "friend.h"
#include "context.h"


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




