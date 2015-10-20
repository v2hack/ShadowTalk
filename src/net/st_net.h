#ifndef ST_NET_H_
#define ST_NET_H_

#include <QString>


class Adapt {
public:
    static void adaptGetLocalIp();
    static void adaptSendMessage(QString channelId, int messageType, QString message);
    static void adaptListenFriends(std::string friendChannelId);
    static void adaptUnistenFriends(std::string friendChannelId);
    static void adaptListenAllFriends();
    static void adaptUnlistenAllFriends();
    static void adaptSendGroupMessage(QString channelId, int messageType, QString message, QString myName);
    static void adaptListenGroups(QString groupChannelId);
    static void adaptListenAllGroups();
};

#endif // ST_NET_H_
