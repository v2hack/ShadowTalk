#ifndef CHATLIST_H
#define CHATLIST_H

#include <QString>

/* ChatItem 节点中的类型 */
#define CHATITEM_TYPE_FRIEND  0
#define CHATITEM_TYPE_GROUP   1

/* chatlist 中的节点成员 */
struct ChatItem
{
    int type;             /* 节点类型，好友或者组 */
    int cacheIndex;       /* 缓存中的索引 */
};

class Chat
{
public:
    /* 加好友到chatList页面 */
    static void addFrientToChat(QString friendName,  QString shortName, int friendIndex, int listViewIndex);

    /* 从chatlist界面删除好友 */
    static void removeFrientFromChat(int chatIndex);

    /* 改变chatlist中item的状态 */
    static void displayChatNetState(int idx, int state);

    /* 设置chatlistview中的未读消息数量 */
    static void displayChatUnreadCount(int idx, int count, int type);

    /* 更新qml中listiew中的索引 */
    static void updateListIndexForChat(int index, int listViewIndex);

    /* 将item在chatlistview中的位置放到首位 */
    static void refreshChatListPosition(int cacheIndex, int itemType);
};


#endif // CHATLIST_H
