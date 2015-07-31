#ifndef CACHE_H
#define CACHE_H

#include <QList>
#include <QObject>
#include "friend.h"


class Cache: public QObject {

    Q_OBJECT

    int friendCount;

public:
    Cache();
    ~Cache();

    QMap<int, Friend> friendList; // 好友列表

    Q_INVOKABLE int getFriendCount();
//    Q_INVOKABLE void insertOneFriend();


};

#endif // CACHE_H
