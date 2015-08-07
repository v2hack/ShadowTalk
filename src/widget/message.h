#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>


/* 消息内容类型 */
enum MessageContentType {
    MessageTypeWord = 1, /* 文字 */
    MessageTypeVoice,    /* 语音 */
    MessageTypeImage,    /* 图片 */
    MessagetypeFile,     /* 文件 */
};

/* 聊天信息内容结构 */
struct Message
{
    int friendIndex; /* 好友map索引 */
    int messageType; /* 聊天信息类型 */

};

/* 聊天消息管理结构 */
class MessageManager : public QObject {
    Q_OBJECT

public:
    MessageManager(QObject *parent = 0);
    ~MessageManager();
    Q_INVOKABLE void sendMessage(int index, QString message);
};

void addMessageToWidget(int uid, QString name, int type, int direct, QString messageData);
void clearMessageFromWidget();
void removeMessageByIndex(int index, int count);

#endif // MESSAGE_H
