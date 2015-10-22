#ifndef CACHE_H
#define CACHE_H

#include <QList>
#include <QObject>
#include <QPointer>
#include <QString>
#include <QMutex>

#include "st_group.h"
#include "st_friend.h"
#include "st_chat.h"


/* 本地创建的二维码和短码 */
struct LocalChannel
{
    QString   channelId;
    QString   shortCode;
    QDateTime createdTime;
    QDateTime expiredTime;
};


/* 缓存数据结构 */
class Cache: public QObject
{
    Q_OBJECT
private:
    int friendCount_;                                      /* 缓存中好友数量 */
    int groupCount_;                                       /* 缓存中组数量 */
public:
    int currentUseId_;                                     /* 界面上当前显示好友id */
    int currentUseType_;                                   /* 界面上当前类型 */
    QString currentUseName_;
    QMap<int, Friend> friendList_;                         /* 联系人列表 */

    QMutex chatMutex_;
    QList<ChatItem *> chatList_;                            /* 聊天列表 */

    QMap<QString, struct LocalChannel *> channelList_;     /* channel映射表 */
    std::map<std::string, std::string> keyValueList_;      /* 密钥映射表 */
    QMap<int, Group> groupList_;                            /* 组列表 */

    Cache();
    ~Cache();
    void CleanCache();                                     /* 清理缓存 */

    /* 联系人操作函数 */
    void insertOneFriend(Friend *newFriend);
    int getNextIndex();
    Friend *getOneFriend(int index);
    Q_INVOKABLE int getFriendCount();
    Q_INVOKABLE void setCurrentId(int id, int type, QString name);
    bool isExistFriend(QString friendChannelId);
    void cleanFriend();

    /* 聊天列表操作 */
    void insertOneChat(int cacheIndex, int type, QString friendName);
    int atFirstPosition(int cacheIndex, int type);
    void removeOneChat(int cacheIndex, int type);
    int getPositionNum(int cacheIndex, int type);

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
