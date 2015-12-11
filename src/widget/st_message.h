#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

/* 消息内容类型 */
enum MessageContentType
{
    MessageTypeNone = 0,            /* 无类型 */
    MessageTypeWord = 1,            /* 文字 */
    MessageTypeImage = 2,           /* 图片 */
    MessageTypeVoice = 3,           /* 语音 */
    MessagetypePCBackup = 7,        /* 同步好友列表 */
    MessagetypePCOffLine = 8,       /* 让pc下线 */
    MessagetypeSyncMessage = 9,     /* 同步好友消息 */
    MessagetypePingPC = 10,         /* ping */
    MessagetypeResponeFromPC = 11,  /* respone to ping */
};

/* 发送方向 */
enum MessageDriectType
{
    MessageDriectMe = 0,     /* 我发的消息 */
    MessageDirectOpposite=1,   /* 对方发的消息 */
};

/* 消息发送方式 */
enum MessageMethod
{
    MessageMethodOnline = 1,  /* 在线消息 */
    MessageMethodOffline,     /* 离线消息 */
};


/* 聊天消息结构 */
struct Message
{
    int driect;             /* 是我的？还是对方的？*/
    int friendIndex;        /* 好友map索引 */
    int messageType;        /* 聊天信息类型 */
    int MessageMethord;     /* 离线或者在线 */
    int voiceSeconds;       /* 如果是语音数据表示秒数 */
    std::string data;       /* 消息内容 */
};

/* 组消消息结构 */
struct GroupMessage
{
    int driect;              /* 是我的？还是对方的？*/
    int friendIndex;         /* 好友map索引 */
    int messageType;         /* 聊天信息类型 */
    int MessageMethord;      /* 离线或者在线 */
    int voiceSeconds;        /* 如果是语音数据表示秒数 */
    std::string senderName;  /* 发送消息人的名字 */
    std::string data;        /* 消息内容 */
};


/* 聊天消息管理结构 */
class MessageManager : public QObject
{
    Q_OBJECT
public:
    MessageManager(QObject *parent = 0);
    ~MessageManager();

    /* qml 界面回调函数 */
    Q_INVOKABLE void sendMessage(QString message);

    /* 发送组消息 */
    void sendGroupMessage(QString &message);

    /* 发送好友消息 */
    void sendFriendMessage(QString &message);
};

/* 消息界面处理类 */
class MessageWidget
{
public:
    /* 添加消息到界面 */
    static void addMessageToWidget(int uid, QString name, int messType,
            int direct, QString messageData, int messageIndex);

    /* 添加图片消息到界面 */
    static void addImageToWidget(int uid, QString name, int messType,
            int direct, std::string messageData,  int messageIndex);

    /* 添加声音到qml界面*/
    static void addVoiceToWidget(int uid, QString name, int type,
            int direct, QString voiceData, int voiceSeconds, int messageIndex);

    /* 清理界面上的所有消息 */
    static void clearMessageFromWidget();

    /* 根据索引删除界面消息 */
    static void removeMessageByIndex(int index, int count);

    /* 清理界面上的所有好友 */
    static void clearFriendFromWidget();
};

#endif // MESSAGE_H
