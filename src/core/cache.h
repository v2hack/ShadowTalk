#ifndef CACHE_H
#define CACHE_H

#include <QList>
#include <QObject>
#include <QPointer>
#include "friend.h"


class Cache: public QObject {

    Q_OBJECT

private:
    int friendCount;               /* 缓存中好友数量 */

public:
    Cache();
    ~Cache();

    int currentUseFriendId;        /* 界面上当前显示好友id */
    QMap<int, Friend> friendList;  /* 好友列表 */

    void insertOneFriend(Friend *newFriend);
    int getNextIndex();
    Friend *getOneFriend(int index);
    Q_INVOKABLE int getFriendCount();
    Q_INVOKABLE void setCurrentFriendId(int id);

};

#endif // CACHE_H
