#include <QDataStream>
#include <QString>
#include <iostream>

#include "st_base64.h"
#include "st_cache.h"
#include "st_context.h"
#include "im.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

std::string Base64::encode(const std::string &binaryData) {
    peersafe::im::Message_client *zebra = gCtx.zebra;
    if (!zebra) {
        qDebug() << "base64 error";
        return "";
    }
	return zebra->base64Encode(binaryData);
}


std::string Base64::decode(const std::string &base64String) {
    peersafe::im::Message_client *zebra = gCtx.zebra;
    if (!zebra) {
        qDebug() << "base64 error";
        return "";
    }
    return zebra->base64Decode(base64String);
}
