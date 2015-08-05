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

extern struct ShadowTalkContext gCtx;


Friend::Friend(QString friendName)
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    newElement.insert("name", friendName);

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(rect, "addFriend", Q_ARG(QVariant, QVariant::fromValue(newElement)));
        qDebug() << "insert one friend ok";
    } else {
        qDebug() << "insert one friend fail";
    }
}


Friend::~Friend()
{



}
