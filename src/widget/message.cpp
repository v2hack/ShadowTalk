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
#include <QString>

#include "friend.h"
#include "context.h"
#include "message.h"

extern struct ShadowTalkContext gCtx;


void addMessageToWidget(int uid, QString name, int type, int direct, QString messageData)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap data;
    data.insert("uid", uid);
    data.insert("name", name);
    data.insert("type", type);
    data.insert("direct", direct);
    data.insert("user_message", messageData);

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addMessage", Q_ARG(QVariant, QVariant::fromValue(data)));
        qDebug() << "insert one message ok";
    } else {
        qDebug() << "insert one message fail";
    }
}

void clearMessageFromWidget() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "clearMessage");
        qDebug() << "clear message ok";
    } else {
        qDebug() << "clear message fail";
    }
    return;
}

void removeMessageByIndex(int index, int count) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap data;
    data.insert("index", index);
    data.insert("count", count);

    QObject *rect = rootObject->findChild<QObject*>("MessageListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "removeMessage", Q_ARG(QVariant, QVariant::fromValue(data)));
        qDebug() << "remove message ok";
    } else {
        qDebug() << "remove message fail";
    }
    return;
}


