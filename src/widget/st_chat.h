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
    static void addFrientToChat(QString friendName,  QString shortName, int friendIndex, int listViewIndex);
    static void removeFrientFromChat(int chatIndex);
    static void displayChatNetState(int idx, int state);
    static void displayChatUnreadCount(int idx, int count);
    static void updateListIndexForChat(int index, int listViewIndex);
    static void refreshChatListPosition(int cacheIndex, int itemType);
};


#endif // CHATLIST_H
