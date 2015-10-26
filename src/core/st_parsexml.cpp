/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_parsexml.cpp
 *  简要描述: 主要负责xml解析处理
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
#include <fstream>
#include "st_parsexml.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_base64.h"
#include "st_zebra.h"
#include "st_net.h"
#include "st_utils.h"
#include "st_log.h"

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

#define ST_XML_TAG_GROUP_CHANNEL_ID     "groupChannelId"
#define ST_XML_TAG_GROUP_MY_ID          "localMemberId"
#define ST_XML_TAG_GROUP_NAME           "name"
#define ST_XML_TAG_GROUP_MY_NAME        "nickNameInGroup"
#define ST_XML_TAG_GROUP_OWNER_ID       "ownerID"
#define ST_XML_TAG_SHOW_NOTIFY          "showNotification"
#define ST_XML_TAG_GROUP_STATUS         "status"

#define ST_XML_TAG_MEMBER_ID            "memberID"
#define ST_XML_TAG_MEMBER_NAME          "name"
#define ST_XML_TAG_MEMBER_STATUS        "status"
#define ST_XML_TAG_MEMBER_GROUP_ID      "groupChannelId"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
*  功能描述: 解析xml keyvalue并加入到cache中
*  @param  key key值
*  @param  value value值
*
*  @return 0 成功  -1 失败
*/
static void addCacheForKeyValue(const QString key, const QString value)
{
    std::string cKey       = key.toStdString();
    std::string cValue     = value.toStdString();
    std::string plainKey   = Base64::decode(cKey);
    std::string plainValue = Base64::decode(cValue);

    Cache *c = gCtx.cache;
    if (!c) {
        qDebug() << "c++: insert cache fail";
        return;
    }

    if (c->isExistChannel(cKey)) {
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
*  @return 无
*/
static void addCacheForChannel(QString &channelId, QString &createdTime,
                               QString &expiredTime, QString &shortCode)
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
*  @return 无
*/
static void addCacheForContact(QString &defaultExpiredTime, QString &friendChannelId,
                               QString &inSession, QString &friendName, QString &netStatus, QString &updateTime)
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

    Friend *newOne = new Friend(friendName, defaultExpiredTime.toInt(), friendChannelId,
                                inSession.toInt(), netStatus.toInt(), gCtx.cache->getNextIndex());
    if (!newOne) {
        return;
    }

    /* 加入缓存 */
    gCtx.cache->insertOneFriend(newOne);
    return;
}

/**
*  功能描述: 将组信息加入到缓存
*  @param  groupChannelId    组channelid
*  @param  localMemberId     本地成员id
*  @param  gourpName         组名称
*  @param  myNameInGroup     自己在组中的名称
*  @param  ownerID           组拥有者id
*  @param  showNotification  有消息是否通知
*  @param  status            组的状态
*
*  @return 无
*/
static void addCacheForGroup(QString groupChannelId, QString localMemberId,
                             QString gourpName, QString myNameInGroup, QString ownerID, QString showNotification,
                             QString status)
{
    int status_ = status.toInt();
    if (status_ < 0) {
        return;
    }

    qDebug() << "c++: addCacheForGroup"
             << " groupChannelId - " << groupChannelId
             << " localMemberId - " << localMemberId
             << " gourpName - " << gourpName
             << " myNameInGroup - " << myNameInGroup
             << " ownerID - " << ownerID
             << " showNotification - " << showNotification
             << " status - " << status;

    /* 名字为空的直接过滤掉 */
    if (gourpName.isEmpty()) {
        return;
    }

    /* 检查好友是否已经存在 */
    if (gCtx.cache->isExistGroup(groupChannelId)){
        return;
    }

    Group *newOne = new Group(groupChannelId, localMemberId, gourpName,
                              myNameInGroup, ownerID, showNotification, gCtx.cache->getNextGroupIndex());
    if (!newOne) {
        return;
    }

    /* 加入缓存 */
    gCtx.cache->insertOneGroup(newOne);
    return;
}

/**
*  功能描述: 将组成员信息加入到缓存
*  @param  memberId         成员id
*  @param  name             成员名称
*  @param  status           成员状态
*  @param  groupChannelId   组的channelid
*
*  @return 无
*/
static void addCacheForGroupMember(QString &memberId, QString &name,
                                   QString &status, QString &groupChannelId)
{
    int status_ = status.toInt();
    if (status_ < 0) {
        return;
    }

    qDebug() << "c++: addCacheForGroupMember"
             << " memberID - " << memberId
             << " name - " << name
             << " status - " << status
             << " groupChannelId - " << groupChannelId;

    /* 检查好友是否已经存在 */
    if (gCtx.cache->isExistGroup(groupChannelId)){
        return;
    }

    /* 找到组 */
    Group *group = gCtx.cache->getOneGroup(groupChannelId);
    if (!group) {
        return;
    }
    /* 检查成员是否已经存在*/
    if (!group->isExistMember(memberId)) {
        group->insertOneMember(memberId, name);
    }
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
int ParseXml::parseContactDict(QDomElement dict)
{
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
int ParseXml::parseContactXml(QDomElement &array)
{
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull(); dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "c++: can't find the dict child";
            return -1;
        } else {
            if (parseContactDict(dict) < 0) {
                return -1;
            }
        }
    }
    return 0;
}

/**
*  功能描述: 解析xml中 QrChannel中的dict标签
*  @param  dict   dict标签元素
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseQrChannelDict(QDomElement dict)
{
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
int ParseXml::parseQrChannelXml(QDomElement &array)
{
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "c++: can't find the dict child";
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
int ParseXml::parseKeyValueDict(QDomElement dict)
{
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
int ParseXml::parseKeyValueXml(QDomElement &array)
{
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "c++: can't find the dict child";
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
*  功能描述: 解析xml中的组的标签
*  @param  array   group中的array标签元素结构
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseGroupDict(QDomElement dict)
{
    QString groupChannelId;
    QString localMemberId;
    QString gourpName;
    QString myNameInGroup;
    QString ownerID;
    QString showNotification;
    QString status;

    QDomNode n = dict.firstChild();
    while (!n.isNull()) {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            if (e.text() == QString(ST_XML_TAG_GROUP_CHANNEL_ID))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            groupChannelId = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_GROUP_MY_ID))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            localMemberId = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_GROUP_NAME))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            gourpName = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_GROUP_MY_NAME))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            myNameInGroup = en.text();
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_GROUP_OWNER_ID))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            ownerID = en.text();
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_SHOW_NOTIFY))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_INTEGER)) {
                            showNotification = en.text();
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_GROUP_STATUS))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_INTEGER)) {
                            status = en.text();
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }

    /* 加入缓存 */
    addCacheForGroup(groupChannelId, localMemberId, gourpName, myNameInGroup, ownerID,
                     showNotification, status);
    return 0;
}


/**
*  功能描述: 解析xml中的组成员标签
*  @param  array   group中的array标签元素结构
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseGroupXml(QDomElement &array)
{
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "c++: can't find the dict child";
            return -1;
        } else {
            if (parseGroupDict(dict) < 0) {
                return -1;
            }
        }
    }
    return 0;
}

/**
*  功能描述: 解析xml中的组的标签
*  @param  array   group中的dict标签元素结构
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseGroupMemberDict(QDomElement dict)
{
    QString memberID;
    QString name;
    QString status;
    QString groupChannelId;

    QDomNode n = dict.firstChild();
    while (!n.isNull()) {
        if (n.isElement())
        {
            QDomElement e = n.toElement();
            if (e.text() == QString(ST_XML_TAG_MEMBER_ID))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            memberID = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_MEMBER_NAME))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            name = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_MEMBER_STATUS))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_INTEGER)) {
                            status = en.text();
                        } else {
                            return -1;
                        }
                    }
                }
            }
            else if (e.text() == QString(ST_XML_TAG_MEMBER_GROUP_ID))
            {
                n = n.nextSibling();
                if (!n.isNull()) {
                    if (n.isElement()) {
                        QDomElement en = n.toElement();
                        if (en.tagName() == QString(ST_XML_TAG_STRING)) {
                            groupChannelId = en.text();
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }

    /* 加入缓存 */
    addCacheForGroupMember(memberID, name, status, groupChannelId);
    return 0;
}

/**
*  功能描述: 解析xml中的组成员标签
*  @param  array   group中的array标签元素结构
*
*  @return 0 成功  -1 失败
*/
int ParseXml::parseGroupMemberXml(QDomElement &array)
{
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "c++: can't find the dict child";
            return -1;
        } else {
            if (parseGroupMemberDict(dict) < 0) {
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
void ParseXml::writeXmlFile(QString plainData)
{
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
 *  功能描述: 过滤xml文件中的回车和tab字符
 *  @param oldData  xml文件内容
 *
 *  @return 返回过滤后的文件内容
 */
QString filterWords(const QString oldData)
{
    std::string newData;
    std::string cppData = oldData.toStdString();
    unsigned long dataSize = cppData.size();

    char *cPtr = new char[dataSize];
    if (cPtr == nullptr) {
        return "";
    }

    memcpy(cPtr, cppData.c_str(), dataSize);

    for (unsigned long i = 0; i < dataSize; i++) {
        if (cPtr[i] == '\t') {
            continue;
        } else if (cPtr[i] == '\n' && cPtr[i + 1] == '\r') {
            i++;
            continue;
        } else {
            newData.insert(newData.end(), cPtr[i]);
        }
    }
    delete [] cPtr;
    return QString::fromStdString(newData);
}

/**
*  功能描述: 解析xml文件入口函数
*  @param  plainData  xml文件明文
*
*  @return 0成功  -1失败
*/
int ParseXml::parseDencryptXml(const QString plainData)
{
    int errLin = 0;
    int errCol = 0;
    QString strError;
    QDomDocument document;

    writeXmlFile(plainData);

    if (!document.setContent(plainData, false, &strError, &errLin, &errCol)) {
        qDebug() << "c++: parse file failed at line " << errLin
                 << " column " << errCol << " " << strError;
        return -1;
    }

    if (document.isNull()) {
        qDebug() << "c++: document is null";
        return -1;
    }

    QDomElement plist = document.documentElement();
    QDomElement rootArray = plist.firstChildElement(ST_XML_TAG_ARRAY);
    QDomElement elt = rootArray.firstChildElement(ST_XML_TAG_ARRAY);

    QDomElement array[5];
    int arrayCount = 0;
    for (int i = 0; !elt.isNull(); elt = elt.nextSiblingElement(ST_XML_TAG_ARRAY), i++) {
        if (i >= 5) {
            break;
        }
        if (elt.isNull()) {
            qDebug() << "c++: can't find the array child";
            return -1;
        } else {
            array[i] = elt;
            arrayCount++;
        }
    }

    if (arrayCount < 3) {
        qDebug() << "c++: xml parse fail, array count is " << arrayCount;
        return -1;
    }

    /* 先解析组 */
    if (arrayCount >= 5) {
        if (parseGroupXml(array[3]) < 0) {
            return -1;
        }
        qDebug() << "c++: parse gourp success";

        if (parseGroupMemberXml(array[4]) < 0) {
            return -1;
        }
        qDebug() << "c++: parse group member success";
    }

    if (parseContactXml(array[0])  < 0) {
        return -1;
    }
    qDebug() << "c++: parse contact success";

    if (parseQrChannelXml(array[1]) < 0) {
        return -1;
    }
    qDebug() << "c++: parse qrchannel success";

    if (parseKeyValueXml(array[2]) < 0) {
        return -1;
    }
    qDebug() << "c++: parse keyvalue success";

    Utils::walkCacheAddFriendAndGroup();
    return 0;
}

/**
*  功能描述: 将数据写入文件
*  @param  fileName  xml文件名
*  @param  data      数据内容
*
*  @return 无
*/
void ParseXml::writeXmlFile(std::string fileName, std::string data)
{
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::binary);
    file.write(data.c_str(), data.size());
    file.close();
    return;
}

/**
 *  功能描述: 解析xml文件
 *  @param fileName   文件名
 *  @param passwd     解密密码
 *
 *  @return
 */
int ParseXml::parseEncryptXml(QString fileName, QString passwd)
{
    QString qPlainData;
    std::string sPasswd = passwd.toStdString();
    std::string sDecryptData;
    std::string sPlainData;
    std::string sEncryptData;
    ParseXml xml;

    /* 读入文件 */
    std::ifstream file;
    file.open(fileName.toStdString().c_str(), std::ios::in | std::ios::binary);
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);
    char *buffer = new char[length];
    if (!buffer) {
        return -1;
    }
    file.read(buffer, length);
    sEncryptData.assign(buffer, length);

    /* 开始解密 */
    sDecryptData = gCtx.zebra_->decrypt(sEncryptData, sPasswd);
    if (sDecryptData.empty()) {
        slog("func<%s> : msg<%s> para<file - %s, pwd - %s>\n",
             "parseEncryptXml", "decrypt xml file fail",
             fileName.toStdString().c_str(), passwd.toStdString().c_str());
        return -1;
    }
    slog("func<%s> : msg<%s> para<file - %s, pwd - %s>\n",
         "parseEncryptXml", "decrypt xml file success",
         fileName.toStdString().c_str(), passwd.toStdString().c_str());

    /* 开始解压 */
    sPlainData = gCtx.zebra_->gzipUncompress(sDecryptData);
    if (sPlainData.empty()) {
        slog("func<%s> : msg<%s> para<file - %s>\n",
             "parseEncryptXml", "uncompress xml file fail", fileName.toStdString().c_str());
        return -1;
    }
    slog("func<%s> : msg<%s> para<file - %s>\n",
         "parseEncryptXml", "uncompress xml file success", fileName.toStdString().c_str());

    qPlainData = QString::fromStdString(sPlainData);
    if (xml.parseDencryptXml(qPlainData) < 0){
        return -1;
    }

    /* 监听好友 */
    Adapt::adaptListenAllFriends();
    /* 监听组 */
    Adapt::adaptListenAllGroups();
    return 0;
}
