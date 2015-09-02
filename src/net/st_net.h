#ifndef ST_NET_H_
#define ST_NET_H_

#include <QString>


void getLocalIp();
void adaptSendMessage(QString channelId, int messageType, QString message, int messageId);
void adaptListenFriends(std::string friendChannelId);
void adaptUnistenFriends(std::string friendChannelId);
void adaptListenAllFriends();
void adaptUnlistenAllFriends();

#endif // ST_NET_H_
