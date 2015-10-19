#ifndef ST_NET_H_
#define ST_NET_H_

#include <QString>


void getLocalIp();

void adaptSendMessage(QString channelId, int messageType, QString message);
void adaptListenFriends(std::string friendChannelId);
void adaptUnistenFriends(std::string friendChannelId);
void adaptListenAllFriends();
void adaptUnlistenAllFriends();

void adaptSendGroupMessage(QString channelId, int messageType, QString message, QString myName);
void adaptListenGroups(QString groupChannelId);
void adaptListenAllGroups();

#endif // ST_NET_H_
