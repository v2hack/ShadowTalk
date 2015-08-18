#include <QDataStream>
#include <QString>
#include <iostream>

#include "st_base64.h"
#include "st_cache.h"
#include "st_context.h"
#include "im.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

QString Base64::encode(const QString &binaryData) {
	return "";
}


QString Base64::decode(const QString &base64String) {
    peersafe::im::Message_client *zebra = gCtx.zebra;
    if (!zebra) {
        qDebug() << "base64 error";
        return "";
    }
    std::string plainString = zebra->base64Decode(base64String.toStdString());
    QString qPlainString = QString::fromStdString(plainString);
    return qPlainString;
}
