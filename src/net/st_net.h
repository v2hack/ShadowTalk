#ifndef ST_NET_H_
#define ST_NET_H_

#include <QString>


void getLocalIp();
void adaptSendMessage(QString channelId, int messageType,
                      QString message, int messageId);

#endif // ST_NET_H_
