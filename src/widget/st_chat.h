#ifndef CHATLIST_H
#define CHATLIST_H

#include <QString>

void addFrientToChat(QString friendName, int friendIndex, int listViewIndex);
void removeFrientFromChat(int chatIndex);
void displayChatNetState(int idx, int state);
void displayChatUnreadCount(int idx, int count);
void updateListIndexForChat(int index, int listViewIndex);

#endif // CHATLIST_H
