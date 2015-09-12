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

#include <iostream>

#include "st_login.h"
#include "st_context.h"
#include "st_utils.h"
#include "st_qrcode.h"

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


/* 将二维码图片设置到页面上 */
void ShadowTalkSetQrImage(QString qrImagePath) {
    QQuickItem *rootObject = gCtx.loginer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("objectLoginSetQrImage");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setQrImage", Q_ARG(QVariant, qrImagePath));
    } else {
        qDebug() << "set login qr image fail";
    }
    return;
}

/* 开始进入同步进度条 */
void ShadowTalkLoginStartSync() {
    QQuickItem *rootObject = gCtx.loginer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("loginQrWindow");
    if (rect) {
        QMetaObject::invokeMethod(rect, "loginQrStartSync");
    } else {
        qDebug() << "login qr start sync fail";
    }
    return;
}

/* 恢复登录界面设置 */
void ShadowTalkLoginClean() {
    QQuickItem *rootObject = gCtx.loginer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("loginQrWindow");
    if (rect) {
        QMetaObject::invokeMethod(rect, "loginQrStartClean");
    } else {
        qDebug() << "login qr clean fail";
    }
    return;
}


/* 登陆 */
int ShadowTalkLogin() {

    int ret = 0, count = 0;
    int tryTimes = 5;

    std::string qrCodeSource;
    std::string qrChannelId;
    std::string qrEnCode;

    /* 检测 impai init 是否成功 */
    ShadowTalkSleep(2000);
    while (1) {
        if (count > tryTimes) {
            return -1;
        }
        ret = gCtx.zebra->get_network_state();
        if (ret < 0) {
            ShadowTalkSleep(1000);
            count++;
            continue;
        } else {
            break;
        }
    }

    /* 利用peersafe接口创建二维码 */
    qrCodeSource = gCtx.zebra->generate_qr_channel(1200);
    if (qrCodeSource.empty()) {
        qDebug() << "generate qr channel fail";
        return -1;
    }
    gCtx.phoneQrChannel = qrCodeSource;

    /* listen 这个channel */
    gCtx.zebra->listen_qr_channel(qrCodeSource);

    /* 转换为特定的channel */
    qrChannelId = gCtx.zebra->hex_encode(qrCodeSource);
    qrEnCode = "C:" + qrChannelId;
    std::cout << "sync qrcode - " << qrEnCode << std::endl;

    /* 创建二维码图片 */
    QrCode code;
    code.setString(QString::fromStdString(qrEnCode));
    if (code.getQRWidth() == 0) {
        qDebug() << "create qrcode fail";
        return 0;
    }
    if (code.saveImage(SHADOW_QR_IMAGE_NAME, 250) == false) {
        qDebug() << "save image fail";
    }

    /* 界面上设置二维码图片*/
    QString tempPath = QString("%0%1").arg(QGuiApplication::applicationDirPath(), SHADOW_QR_IMAGE_NAME);
    const QUrl pictureUrl = QUrl::fromLocalFile(tempPath);
    ShadowTalkSetQrImage(pictureUrl.toString());
    return 0;
}

