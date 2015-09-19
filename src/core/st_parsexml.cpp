/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_parsexml.cpp
 *  简要描述:
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QDateTime>
#include <QDebug>

#include <iostream>

#include "st_parsexml.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_base64.h"
#include "st_zebra.h"
#include "st_net.h"
#include "st_utils.h"

#define ST_XML_TAG_DICT                 "dict"
#define ST_XML_TAG_ARRAY                "array"
#define ST_XML_TAG_KEY                  "key"
#define ST_XML_TAG_DATA                 "data"
#define ST_XML_TAG_STRING               "string"
#define ST_XML_TAG_DATE                 "date"
#define ST_XML_TAG_INTEGER              "integer"
#define ST_XML_TAG_VALUE                "value"

#define ST_XML_TAG_EXPIRED_TIME         "expiredTime"
#define ST_XML_TAG_CHANNELID            "channelId"
#define ST_XML_TAG_CREATED_TIME         "createdTime"
#define ST_XML_TAG_SHORT_CODE           "shortCode"

#define ST_XML_TAG_DEFAULT_EXPIRED_TIME "defaultExpiredTime"
#define ST_XML_TAG_FRIEND_CHANNEL_ID    "friendChannelId"
#define ST_XML_TAG_INSESSION            "inSession"
#define ST_XML_TAG_NAME                 "name"
#define ST_XML_TAG_STATUS               "status"
#define ST_XML_TAG_UPDATER_TIME         "updateTime"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;



/**
*  功能描述: 解析xml keyvalue并加入到cache中
*  @param  key key值
*  @param  value value值
*
*  @return 0 成功  -1 失败
*/
void addCacheForKeyValue(QString key, QString value) {
    std::string cKey = key.toStdString();
    std::string cValue = value.toStdString();

    std::string plainKey   = Base64::decode(cKey);
    std::string plainValue = Base64::decode(cValue);

    Cache *c = gCtx.cache;
    if (!c) {
        qDebug() << "insert cache fail";
        return;
    }

    if (c->isExistChannel(cKey)){
        return;
    }

    c->insertKeyValue(plainKey,  plainValue);
    return;
}

/**
*  功能描述: 解析xml channel并加入到cache中
*  @param  channelId      channel索引
*  @param  createdTime    创建时间
*  @param  expiredTime    过期时间
*  @param  shortCode      短码
*
*  @return 0 成功  -1 失败
*/
void addCacheForChannel(
        QString &channelId,
        QString &createdTime,
        QString &expiredTime,
        QString &shortCode)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    if (c->isExistChannel(channelId)) {
        return;
    }

    struct LocalChannel *newOne = new LocalChannel;
    if (!newOne) {
        return;
    }

    newOne->channelId   = channelId;
    newOne->shortCode   = shortCode;
    newOne->createdTime = QDateTime::fromString(createdTime, "yyyy-MM-ddTHH-mm-ssZ");
    newOne->expiredTime = QDateTime::fromString(expiredTime, "yyyy-MM-ddTHH-mm-ssZ");
    c->insertChannel(newOne);
    return;
}


/**
*  功能描述: 将联系人信息加入到缓存
*  @param  defaultExpiredTime  默认超时时间
*  @param  friendChannelId     好友channel索引
*  @param  inSession           是否在聊天列表中
*  @param  friendName          好友名字
*  @param  netStatus           网络状态
*  @param  updateTime          更新时间
*
*  @return 0 成功  -1 失败
*/
void addCacheForContact(
        QString defaultExpiredTime,
        QString friendChannelId,
        QString inSession,
        QString friendName,
        QString netStatus,
        QString updateTime)
{
    updateTime = updateTime;

    /* 名字为空的直接过滤掉 */
    if (friendName.isEmpty()) {
        return;
    }

    /* 检查好友是否已经存在 */
    if (gCtx.cache->isExistFriend(friendChannelId)){
        return;
    }

    Friend *newOne = new Friend(
                friendName,
                defaultExpiredTime.toInt(),
                friendChannelId,
                inSession.toInt(),
                netStatus.toInt(),
                gCtx.cache->getNextIndex());
    if (!newOne) {
        return;
    }


    /* 加入缓存 */
    gCtx.cache->insertOneFriend(newOne);
    return;
}


ParseXml::ParseXml() {
}
ParseXml::~ParseXml() {
}

/**
*  功能描述: 解析xml中联系人所有元素
*  @param  array   联系人中的array标签元素结构
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseContactDict(QDomElement dict) {

    QString defaultExpiredTime;
    QString friendChannelId;
    QString inSession;
    QString friendName;
    QString netStatus;
    QString updateTime;

    QDomNode n = dict.firstChild();
    while (!n.isNull()) {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            if (e.text() == QString(ST_XML_TAG_DEFAULT_EXPIRED_TIME))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_INTEGER)) {
                            defaultExpiredTime = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            } else if (e.text() == QString(ST_XML_TAG_FRIEND_CHANNEL_ID)) {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            friendChannelId = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            } else if (e.text() == QString(ST_XML_TAG_INSESSION)) {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_INTEGER)) {
                            inSession = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            } else if (e.text() == QString(ST_XML_TAG_NAME)) {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            friendName = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            } else if (e.text() == QString(ST_XML_TAG_STATUS)) {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_INTEGER)) {
                            netStatus = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            } else if (e.text() == QString(ST_XML_TAG_UPDATER_TIME)) {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_DATE)) {
                            updateTime = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }

    /* 加入缓存 */
    addCacheForContact(defaultExpiredTime, friendChannelId,
            inSession, friendName, netStatus, updateTime);

    return 0;
}

/**
*  功能描述: 解析xml中联系人标签元素
*  @param  dict  dict标签元素
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseContactXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull(); dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++) {
        if (dict.isNull()) {
            qDebug() << "can't find the dict child";
            return -1;
        } else {
            if (parseContactDict(dict) < 0) {
                return -1;
            }
        }
    }
    walkCacheAddFriend();
}

/**
*  功能描述: 解析xml中 QrChannel中的dict标签
*  @param  dict   dict标签元素
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseQrChannelDict(QDomElement dict) {

    QString channelId;
    QString createdTime;
    QString expiredTime;
    QString shortCode;

    QDomNode n = dict.firstChild();
    while (!n.isNull()) {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            if (e.text() == QString(ST_XML_TAG_CHANNELID))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            channelId = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_CREATED_TIME))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_DATE)) {
                            createdTime = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_EXPIRED_TIME))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_DATE)) {
                            expiredTime = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_SHORT_CODE))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            shortCode = en.text();
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }

    /* 加入缓存 */
    addCacheForChannel(channelId, createdTime, expiredTime, shortCode);
    return 0;
}


/**
*  功能描述: 解析xml中二维码channel标签
*  @param  array   二维码channel中的array标签元素结构
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseQrChannelXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "can't find the dict child";
            return -1;
        } else {
            if (parseQrChannelDict(dict) < 0) {
                return -1;
            }
        }
    }
    return 0;
}

/**
*  功能描述: 解析xml中 keyValue中的dict标签
*  @param  dict   dict标签元素
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseKeyValueDict(QDomElement dict) {

    QString key;
    QString value;

    QDomNode n = dict.firstChild();
    while (!n.isNull()) {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            if (e.text() == QString(ST_XML_TAG_KEY))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_DATA)) {
                            key = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_VALUE))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_DATA)) {
                            value = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }

    /* 加入到缓存 */
    addCacheForKeyValue(key, value);
    return 0;
}

/**
*  功能描述: 解析xml中的array下的所有内容
*  @param  array   keyvalue中的array标签元素结构
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseKeyValueXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "can't find the dict child";
            return -1;
        } else {
            if (parseKeyValueDict(dict) < 0) {
                return -1;
            }
        }
    }
    return 0;
}


/**
*  功能描述: 写xml明文文件
*  @param  plainData  xml文件明文
*
*  @return 无
*/
void ParseXml::writeXmlFile(QString plainData) {
    QFile f("ShadTalk.xml");
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream txtOutput(&f);
    txtOutput << plainData;
    f.close();
    return;
}


/**
*  功能描述: 解析xml文件入口函数
*  @param  plainData  xml文件明文
*
*  @return 0成功  -1失败
*/
int ParseXml::parseDencryptXml(const QString plainData) {

    writeXmlFile(plainData);

    QDomDocument document;
    QString strError;
    int errLin = 0, errCol = 0;

    if (!document.setContent(plainData, false, &strError, &errLin, &errCol)) {
        qDebug() << "parse file failed at line " << errLin << " column " << errCol << " " << strError;
        return -1;
    }

    if (document.isNull()) {
        qDebug() << "document is null";
        return -1;
    }

    QDomElement plist = document.documentElement();
    QDomElement rootArray = plist.firstChildElement(ST_XML_TAG_ARRAY);
    QDomElement elt = rootArray.firstChildElement(ST_XML_TAG_ARRAY);

    QDomElement array[3];
    for (int i = 0; !elt.isNull(); elt = elt.nextSiblingElement(ST_XML_TAG_ARRAY), i++) {
        if (elt.isNull()) {
            qDebug() << "can't find the array child";
            return -1;
        } else {
            array[i] = elt;
        }
    }

    if (parseContactXml(array[0])  < 0) {
        return -1;
    }
    if (parseQrChannelXml(array[1]) < 0) {
        return -1;
    }
    if (parseKeyValueXml(array[2]) < 0) {
        return -1;
    }
    return 0;
}
