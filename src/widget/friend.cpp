/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称:
 *  简要描述:
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include <QWidget>
#include <QtQuick/QQuickView>

#include "friend.h"
#include "context.h"
#include "log.h"
#include "message.h"

extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 初始化一个好友
 *  @param friendIndex 好友索引
 *  @param friendName 好友名称
 *  @return 无
 */
Friend::Friend(QString friendName, int friendIndex):
    name(friendName), messageCount(0) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    newElement.insert("friendName", friendName);
    newElement.insert("friendIndex", friendIndex);

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addFriend", Q_ARG(QVariant, QVariant::fromValue(newElement)));
        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             __func__, "add friend to widget success", friendIndex, friendName.toLatin1().data());
    } else {
        slog("func<%s> : msg<%s> para<friendName - %d, friendIndex - %s>\n",
             __func__, "add friend to widget fail", friendIndex, friendName.toLatin1().data());
    }
}

Friend::~Friend() {

}

/**
 *  功能描述: 将消息放入缓存列表
 *  @return 无
 */
void Friend::insertOneMessage(Message *message) {
    this->messageList.insert(this->messageList.size() + 1, *message);
    return;
}


/**
 *  功能描述: 存储二维码到缓存
 *  @return 无
 */
void Friend::setQrCode(QString qrCode) {
    this->qrCode = qrCode;
}

/**
 *  功能描述: 存储名字到缓存
 *  @return 无
 */
void Friend::setName(QString name) {
    this->name = name;
}

/**
 *  功能描述: SelectFriend构造函数
 *  @return 无
 */
void Friend::setNetState(int state) {
    this->netState = state;
}

/**
 *  功能描述: SelectFriend构造函数
 *  @return 无
 */
SelectFriend::SelectFriend(QObject *parent) {

}


/**
 *  功能描述: SelectFriend的析构函数
 *  @return 无
 */
SelectFriend::~SelectFriend() {

}

/**
 *  功能描述: 改变界面上的消息列表
 *  @param index 好友索引
 *  @param name 好友名称
 *  @return 无
 */
void SelectFriend::changeMessageList(int index, QString name) {
    /* 清理界面消息 */
    clearMessageFromWidget();

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    /* 找到好友缓存 */
    Friend *f = c->getOneFriend(index);
    if (!f) {
        qDebug() << "can't find friend index - " << index;
        return;
    }

    /* 设置当前好友index */
    c->setCurrentFriendId(index);

    qDebug() << "message list size - " << f->messageList.size();

    /* 添加消息 */
    for (int i = 0; i < f->messageList.size(); i++) {
        QMap<int, Message>::iterator it = f->messageList.find(i + 1);
        if (it == f->messageList.end()) {
            return;
        }

        /* 设置显示名字 */
        QString name;
        if (it->driect == MessageDriectMe) {
            name = "Me";
        } else {
            name = f->name;
        }
        /* 添加消息到界面 */
        addMessageToWidget(f->id.toInt(), name, it->messageType, it->driect, it->data);
    }
    return;
}
