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
#include <Qstring>
#include <QWidget>
#include <QtQuick/QQuickView>

#include "login.h"
#include "context.h"
#include "utils.h"

extern struct ShadowTalkContext gCtx;

/* 设置界面上的同步进度 */
void ShadowTalkSetSyncProcess(int processValue) {
    QQuickItem *rootObject = gCtx.loginer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariant newProcessValue = processValue;
    QObject *rect = rootObject->findChild<QObject*>("objectLoginProcessPaint");
    if (rect) {
        QMetaObject::invokeMethod(rect, "processPaint", Q_ARG(QVariant, newProcessValue));
    } else {
        qDebug() << "paint login process fail";
    }
    return;
}


/* 生成二维码 */
QString ShadowTalkCreateQrCode(QString qrCodeSource) {



}

/* 将二维码图片设置到页面上 */
void ShadowTalkQrImage(QString qrImagePath) {

}


/* 添加好友控件 */
void ShadowTalkAddFriendWidget() {
    // 添加控件

    // 好友添加到cache
    return;
}


/* 登陆 */
int ShadowTalkLogin() {
    QString qrCodeSource;

    /* 利用peersafe接口创建二维码 */
    //qrCodeSource = XXX

    /* 创建二维码图片 */
    QString qrImagePath = ShadowTalkCreateQrCode(qrCodeSource);
    if (qrImagePath.isEmpty()) {
        return ST_CREATE_QRCODE_FAIL;
    }

    /* 界面上设置二维码图片*/
    ShadowTalkQrImage(qrImagePath);
    return ST_SUCCESS;
}


