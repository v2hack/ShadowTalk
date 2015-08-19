/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_base64.cpp
 *  简要描述: base64 接口封装
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
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
