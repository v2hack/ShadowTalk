#ifndef ST_FRIEND_H_
#define ST_FRIEND_H_

#include <QObject>
#include <QQuickItem>
#include <QGuiApplication>

#include <QString>
#include <QTime>
#include <QMap>
#include "message.h"

#include <QtQuick/QQuickView>

class Friend : public QObject {

Q_OBJECT


public:
    Friend(QString name);
    ~Friend();

    QString name;   // 用户名
    QString qrCode; // 二维码
    QString index;  // 索引值

    int netState;   // 网络状态
    QTime time;     // 上线时间

    QMap<int, Message> messageList; // 消息列表

};













#endif //ST_FRIEND_H_
