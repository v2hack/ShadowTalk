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
#include <QString>
#include <QHostInfo>
#include <QDebug>

#include <iostream>

#include "st_context.h"
#include "st_cache.h"
#include "st_net.h"
#include "st_zebra.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

void getLocalIp() {
    QString localHostName = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(localHostName);
    qDebug() << "IP Address: "<< info.addresses();
    return;
}


void adaptSendMessage(QString channelId, int messageType,
                      QString message, int messageId) {
    peersafe::im::Message_client *z = gCtx.zebra;
    if (z) {

        std::cout << "friend channel id - " << channelId.toStdString() << std::endl;
        z->send_offline_message(StringToHex(channelId.toStdString()),
                                messageType,
                                message.toStdString(),
                                60, 60, 0, message.size(), messageId);
    }
    return;
}
