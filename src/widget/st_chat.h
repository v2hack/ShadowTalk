#ifndef CHATLIST_H
#define CHATLIST_H

#include <QString>

void addFrientToChat(QString friendName,  QString shortName, int friendIndex, int listViewIndex);
void removeFrientFromChat(int chatIndex);
void displayChatNetState(int idx, int state);
void displayChatUnreadCount(int idx, int count);
void updateListIndexForChat(int index, int listViewIndex);

void refreshChatListPosition(int cacheIndex, int itemType);

/* ChatItem 节点中的类型 */
#define CHATITEM_TYPE_FRIEND  0
#define CHATITEM_TYPE_GROUP   1


/* chatlist 中的节点成员 */
struct ChatItem {
    int type;            /* 节点类型，好友或者组 */
    int cacheIndex;      /* 缓存中的索引 */
    int friendListIndex;
};


#endif // CHATLIST_H
