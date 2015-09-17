#ifndef CACHE_H
#define CACHE_H

#include <QList>
#include <QObject>
#include <QPointer>
#include <QString>

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

    void CleanCache();

    int currentUseFriendId;                    /* 界面上当前显示好友id */
    QMap<int, Friend> friendList;              /* 联系人列表 */
    QList<int> chatList;                       /* 聊天列表 */
    QMap<QString, struct LocalChannel *> channelList;  /* channel映射表 */
    std::map<std::string, std::string> keyValueList;   /* 密钥映射表 */

    /* 联系人操作函数 */
    void insertOneFriend(Friend *newFriend);
    int getNextIndex();
    Friend *getOneFriend(int index);
    Q_INVOKABLE int getFriendCount();
    Q_INVOKABLE void setCurrentFriendId(int id);
    void cleanFriend();

    /* 聊天列表操作 */
    void insertOneChat(int friendListId, QString friendName);
    int atFirstPosition(int friendListId);
    void removeOneChat(int friendListId);
    int getFriendIdOfChat(int chatId);

    /* channel操作函数 */
    struct LocalChannel *getChannel(QString channelId);
    void insertChannel(struct LocalChannel *channel);
    void deleteChannel(QString channeldId);
    void cleanChannel();

    /* 密钥操作函数 */
    std::string getKeyValue(std::string key);
    void insertKeyValue(std::string key, std::string value);
    void deleteKeyValue(std::string key);
    void cleanKeyValue();

};

#endif // CACHE_H
