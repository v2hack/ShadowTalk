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

int Cache::getNextIndex() {
    return this->getFriendCount() + 1;
}


int Cache::getFriendCount() {
    return friendList.size();
}

void Cache::setCurrentFriendId(int id) {
    this->currentUseFriendId = id;
}


Friend *Cache::getOneFriend(int index) {
    QMap<int, Friend>::iterator it = friendList.find(index);
    if (it == friendList.end()) {
        return nullptr;
    }
    return &(*it);
}


void Cache::insertOneFriend(Friend *newFriend) {
    this->friendCount++;
    friendList.insert(this->friendCount, *newFriend);
    return;
}




