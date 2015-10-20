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
#include <regex>

#include "st_base64.h"
#include "st_cache.h"
#include "st_context.h"
#include "im.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: encode 将二进制数据变成可见字符串
 *  @param binaryData  二进制数据
 *
 *  @return 无
 */
std::string Base64::encode(const std::string &binaryData)
{
    peersafe::im::Message_client *zebra = gCtx.zebra;
    if (!zebra) {
        return "";
    }
    return zebra->base64Encode(binaryData);;
}

/**
 *  功能描述: 过滤xml文件中的回车和tab字符
 *  @param oldData  xml文件内容
 *
 *  @return 返回过滤后的文件内容
 */
static std::string filterWords(const std::string oldData)
{
    std::string newData;
    unsigned long dataSize = oldData.size();
    char *cPtr = new char[dataSize];
    if (cPtr == nullptr) {
        return "";
    }
    memcpy(cPtr, oldData.c_str(), dataSize);

    for (unsigned long i = 0; i < dataSize; i++) {
        if (cPtr[i] == '\t' || cPtr[i] == '\n') {
            continue;
        } else {
            newData.insert(newData.end(), cPtr[i]);
        }
    }
    delete [] cPtr;
    return newData;
}

/**
 *  功能描述: decode 将字符串变成二进制数据
 *  @param base64String  可见字符串
 *
 *  @return 无
 */
std::string Base64::decode(const std::string &base64String)
{
    peersafe::im::Message_client *zebra = gCtx.zebra;
    if (!zebra) {
        return "";
    }
    std::string new_s = zebra->base64Decode(filterWords(base64String));
    return new_s;
}
