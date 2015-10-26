#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QQuickItem>
#include "st_message.h"

/*
*  类名: Group
*  用途: 组结构
*/
class Group
{
public:
    Group(QString groupChannelId, QString localMemberId, QString gourpName,
       QString myNameInGroup, QString ownerID, QString showNotification, int gid);
    ~Group();

    QMap<int, GroupMessage> messageList_;  // 消息列表 qmlId:struct
    QMap<QString , QString> memberList_;   // 成员列表 memberID:name

    QString groupChannelId_;      // 组通道id
    QString localMemberId_;       // 本地成员id
    QString gourpName_;           // 组名称
    QString myNameInGroup_;       // 自己在组中的名称
    QString ownerID_;             // 组拥有这的id
    QString showNotification_;    // 是否显示通知

    int cacheIndex_;              // 组在缓存中的索引
    int listViewIndex_;           // 组在friendListView中的索引
    int messageUnreadCount_;      // 未读消息数量

    /* 将一个消息加入缓存 */
    void insertOneMessage(GroupMessage *message);

    /* 将一个组成员加入到组 */
    void insertOneMember(QString &memberId, QString &name);

    /* 判断一个组成员是否存在 */
    bool isExistMember(QString &memberId);

    /* 设置friendlistView中的item背景色为透明 */
    void setFriendlistBackGroundColor(int colorFlag);

    /* 设置chatlistView中的item背景色为透明 */
    void setChatlistBackGroundColor(int colorFlag, int chatListIndex);
};


/*
*  类名: SelectGroup
*  用途: 界面点击好友，动态切换聊天内容
*/
class SelectGroup : public QObject
{
    Q_OBJECT
public:
    SelectGroup(QObject *parent = 0);
    ~SelectGroup();

    /* 改变friendListView界面上的消息列表 */
    Q_INVOKABLE void changeMessageListForFlist(int index, QString name);

    /* 改变chatListView界面上的消息列表 */
    Q_INVOKABLE void changeMessageListForClist(int index, QString name);

    /* 将组的消息刷新的到界面 */
    void refreshGroupMessage(Group *g);

    /* 刷新组界面上的未读消息数量 */
    void refreshGroupStatistics(Group *g);
};


#endif // GROUP_H

