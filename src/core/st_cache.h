#ifndef CACHE_H
#define CACHE_H

#include <QList>
#include <QObject>
#include <QPointer>
#include <QString>

#include "st_group.h"
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
    int friendCount;                                  /* 缓存中好友数量 */
    int groupCount;                                   /* 缓存中组数量 */
public:
    Cache();
    ~Cache();

    void CleanCache();                                 /* 清理缓存 */

    int currentUseId;                                  /* 界面上当前显示好友id */
    int currentUseType;                                /* 界面上当前类型 */

    QMap<int, Friend> friendList;                      /* 联系人列表 */
    QList<int> chatList;                               /* 聊天列表 */
    QMap<QString, struct LocalChannel *> channelList;  /* channel映射表 */
    std::map<std::string, std::string> keyValueList;   /* 密钥映射表 */
    QMap<int, Group> groupList;                        /* 组列表 */


    /* 联系人操作函数 */
    void insertOneFriend(Friend *newFriend);
    int getNextIndex();
    Friend *getOneFriend(int index);
    Q_INVOKABLE int getFriendCount();
    Q_INVOKABLE void setCurrentId(int id, int type);
    bool isExistFriend(QString friendChannelId);
    void cleanFriend();

    /* 聊天列表操作 */
    void insertOneChat(int friendListId, QString friendName);
    int atFirstPosition(int friendListId);
    void removeOneChat(int friendListId);
    int getFriendIdOfChat(int chatId);
    int getPositionNum(int friendListId);

    /* channel操作函数 */
    struct LocalChannel *getChannel(QString channelId);
    void insertChannel(struct LocalChannel *channel);
    void deleteChannel(QString channeldId);
    bool isExistChannel(QString channelId);
    void cleanChannel();

    /* 密钥操作函数 */
    std::string getKeyValue(std::string key);
    void insertKeyValue(std::string key, std::string value);
    void deleteKeyValue(std::string key);
    bool isExistChannel(std::string key);
    void cleanKeyValue();

    /* 组操作函数 */
    void insertOneGroup(Group *newGroup);
    int getNextGroupIndex();
    Q_INVOKABLE int getGroupCount();
    Group *getOneGroup(int index);
    Group *getOneGroup(QString groupChannelId);
    bool isExistGroup(QString groupChannelId);
    void cleanGroup();

};

#endif // CACHE_H
