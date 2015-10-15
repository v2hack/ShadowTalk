#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QQuickItem>
#include "st_message.h"

class Group {

public:

    Group(QString groupChannelId, QString localMemberId, QString gourpName,
          QString myNameInGroup, QString ownerID, QString showNotification, int gid);
    ~Group();

    int gid_;
    QString groupChannelId_;
    QString localMemberId_;
    QString gourpName_;
    QString myNameInGroup_;
    QString ownerID_;
    QString showNotification_;

    int listViewIndex;
    int messageUnreadCount;

    QMap<int, GroupMessage> messageList;  // 消息列表 qmlId:struct
    QMap<QString , QString> memberList;   // 成员列表 memberID:name

    void insertOneMessage(GroupMessage *message);
    void insertOneMember(QString &memberId, QString &name);
    bool isExistMember(QString &memberId);
    void setFriendlistBackGroundColor(int colorFlag);
    void setChatlistBackGroundColor(int colorFlag, int chatListIndex);
};


/*
*  类名: SelectFriend
*  用途: 界面点击好友，动态切换聊天内容
*/
class SelectGroup : public QObject {
    Q_OBJECT

public:
    SelectGroup(QObject *parent = 0);
    ~SelectGroup();
    Q_INVOKABLE void changeMessageListForGroup(int index, QString name);
};


#endif // GROUP_H

