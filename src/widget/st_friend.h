#ifndef ST_FRIEND_H_
#define ST_FRIEND_H_

#include <QObject>
#include <QQuickItem>
#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QString>
#include <QTime>
#include <QMap>

#include "st_message.h"

/*
*  类名: Friend
*  用途: 好友信息维护类
*/
class Friend{
public:
    Friend(QString name, int friendIndex);
    Friend(QString friendName, int expiredTime, QString channelId,
                   int session, int status, int friendIndex);
    ~Friend();

    int cacheIndex;                          // 好友id,用于界面
    QString qrCode;                  // 二维码
    int defaultExpiredTime;          // 默认的超时时间
    QString friendChannelId;         // 好友通道
    int inSession;                   // 联系人是否在聊天列表中
    QString name;                    // 用户名
    QString firstLetter;
    int netStatus;                   // 在线状态
    int loadStatus;                  // 是否已经加载到界面
    int listViewIndex;               // 在listView中排序

    int messageCount;                // 消息数量
    int messageUnreadCount;          // 消息未读数量
    QMap<int, Message> messageList;  // 消息列表

    void insertOneMessage(Message *message);
    void setQrCode(QString qrCode);
    void setName(QString name);
    void setNetState(int state);
    void displayUnreadCount(int index, int count);
    void setTimeAndState(int idx, int state);
    void setFriendlistBackGroundColor(int colorFlag);
    void setChatlistBackGroundColor(int colorFlag, int chatListIndex);
};


/*
*  类名: SelectFriend
*  用途: 界面点击好友，动态切换聊天内容
*/
class SelectFriend : public QObject {
    Q_OBJECT

public:
    SelectFriend(QObject *parent = 0);
    ~SelectFriend();
    Q_INVOKABLE void changeMessageListForFlist(int index, QString name);
    Q_INVOKABLE void changeMessageListForClist(int index, QString name);
    void refreshFriendMessage(Friend *f);
    void refreshFriendStatistics(Friend *f);
};

#endif //ST_FRIEND_H_
