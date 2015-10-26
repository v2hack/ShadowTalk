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
    Friend(QString friendName, int expiredTime,
           QString channelId, int session, int status, int friendIndex);
    ~Friend();

    QMap<int, Message> messageList;   // 消息列表

    QString qrCode_;                  // 二维码
    QString friendChannelId_;         // 好友通道
    QString name_;                    // 用户名
    QString firstLetter_;             // 名字的首字母

    int cacheIndex_;                  // 缓存索引
    int defaultExpiredTime_;          // 默认的超时时间， 目前没有使用
    int inSession_;                   // 联系人是否在聊天列表中, 目前没有使用
    int netStatus_;                   // 在线状态
    int loadStatus_;                  // 是否已经加载到界面
    int listViewIndex_;               // 在friendListView中排序
    int messageCount_;                // 消息数量
    int messageUnreadCount_;          // 消息未读数量

    /* 将消息放入缓存列表 */
    void insertOneMessage(Message *message);

    /* 调用qml对象，设置好友界面未读消息数量*/
    void displayUnreadCount(int index, int count);

    /* 调用qml对象，设置好友界面未读消息数量 */
    void setTimeAndState(int idx, int state);

    /* 设置friendlistView中的item背景色为透明 */
    void setFriendlistBackGroundColor(int colorFlag);

    /* 设置chatlistView中的item背景色为透明 */
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

    /* 选中friendListVieww 改变界面上的消息列表 */
    Q_INVOKABLE void changeMessageListForFlist(int index, QString name);

    /* 选中chatListView 改变界面上的消息列表 */
    Q_INVOKABLE void changeMessageListForClist(int index, QString name);

    /* 根据选中的listView上的item，刷新界面上的消息 */
    void refreshFriendMessage(Friend *f);

    /* 根据选中的listView上的item，刷新界面上的未读消息数量 */
    void refreshFriendStatistics(Friend *f);
};

#endif //ST_FRIEND_H_
