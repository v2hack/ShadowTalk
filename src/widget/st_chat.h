#ifndef CHATLIST_H
#define CHATLIST_H

#include <QString>

void addFrientToChat(QString friendName, int friendIndex);
void removeFrientFromChat(int chatIndex);
void displayChatNetState(int idx, int state);
void displayChatUnreadCount(int idx, int count);

#endif // CHATLIST_H
