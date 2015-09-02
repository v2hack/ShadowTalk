#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

/* 消息内容类型 */
enum MessageContentType {
    MessageTypeNone = 0,
    MessageTypeWord = 1, /* 文字 */
    MessageTypeImage = 2,    /* 图片 */
    MessageTypeVoice = 3,    /* 语音 */

    MessagetypePCBackup = 7,
    MessagetypePCOffLine = 8,
    MessagetypeSyncMessage = 9,
    MessagetypePingPC = 10,
    MessagetypeResponeFromPC = 11,
};

/* 发送方向 */
enum MessageDriectType {
    MessageDriectMe = 1,   /* 我发的消息 */
    MessageDirectOpposite, /* 对方发的消息 */
};

/* 消息发送方式 */
enum MessageMethod {
    MessageMethodOnline = 1, /* 在线消息 */
    MessageMethodOffline,    /* 离线消息 */
};


/* 聊天信息内容结构 */
struct Message
{
    int driect;         /* 是我的？还是对方的？*/
    int friendIndex;    /* 好友map索引 */
    int messageType;    /* 聊天信息类型 */
    int MessageMethord; /* 离线或者在线 */
    int voiceSeconds;   /* 如果是语音数据表示秒数 */
    std::string data;       /* 消息内容 */
};

/* 聊天消息管理结构 */
class MessageManager : public QObject {
    Q_OBJECT

public:
    MessageManager(QObject *parent = 0);
    ~MessageManager();
    Q_INVOKABLE void sendMessage(int index, QString message);
};

void addMessageToWidget(
        int uid,
        QString name,
        int messType,
        int direct,
        QString messageData,
        int messageIndex);

void addImageToWidget(
        int uid,
        QString name,
        int type,
        int direct,
        std::string messageData,
        int messageIndex);

void addVoiceToWidget(
        int uid,
        QString name,
        int type,
        int direct,
        QString voiceData,
        int voiceSeconds,
        int messageIndex);

void clearMessageFromWidget();
void removeMessageByIndex(int index, int count);
void clearFriendFromWidget();

#endif // MESSAGE_H
