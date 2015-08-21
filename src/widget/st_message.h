#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

#define SHADOWTALK_TEMP_DIR       "temp"  /* 临时文件目录 */
#define SHADOWTALK_IMAGE_PREFIX   ".img"  /* 图片文件扩展名 */
#define SHADOWTALK_SOUND_PREFIX   ".snd"  /* 声音文件扩展名 */

/* 消息内容类型 */
enum MessageContentType {
    MessageTypeNone = 0,
    MessageTypeWord, /* 文字 */
    MessageTypeImage,    /* 图片 */
    MessageTypeVoice,    /* 语音 */
    MessagetypeFile,     /* 文件 */
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
    QString data;       /* 消息内容 */
};

/* 聊天消息管理结构 */
class MessageManager : public QObject {
    Q_OBJECT

public:
    MessageManager(QObject *parent = 0);
    ~MessageManager();
    Q_INVOKABLE void sendMessage(int index, QString message);
};

void addMessageToWidget(int uid, QString name, int messType, int direct, QString messageData);
void addImageToWidget(int uid, QString name, int type, int direct, QString messageData);
void addVoiceToWidget(int uid, QString name, int type, int direct, QString voiceData, int voiceSeconds);

void clearMessageFromWidget();
void removeMessageByIndex(int index, int count);

#endif // MESSAGE_H
