#ifndef CACHE_H
#define CACHE_H

#include <QList>
#include <QObject>
#include <QPointer>
#include "st_friend.h"


/* 本地创建的二维码和短码 */
struct LocalChannel {
    QString channelId;
    QString shortCode;
    QDateTime createdTime;
    QDateTime expiredTime;
};


/* 缓存数据结构 */
class Cache: public QObject {
    Q_OBJECT
private:
    int friendCount;                          /* 缓存中好友数量 */
public:
    Cache();
    ~Cache();

    int currentUseFriendId;                    /* 界面上当前显示好友id */
    QMap<int, Friend> friendList;              /* 好友列表 */
    QMap<QString, struct LocalChannel *> channelList;  /* channel映射表 */
    QMap<QString, QString> keyValueList;      /* 密钥映射表 */


    /* 好友操作函数 */
    void insertOneFriend(Friend *newFriend);
    int getNextIndex();
    Friend *getOneFriend(int index);
    Q_INVOKABLE int getFriendCount();
    Q_INVOKABLE void setCurrentFriendId(int id);

    /* channel操作函数 */
    struct LocalChannel *getChannel(QString channelId);
    void insertChannel(struct LocalChannel *channel);
    void deleteChannel(QString channeldId);

    /* 密钥操作函数 */
    QString getKeyValue(QString key);
    void insertKeyValue(QString key, QString value);
    void deleteKeyValue(QString key);
};

#endif // CACHE_H
