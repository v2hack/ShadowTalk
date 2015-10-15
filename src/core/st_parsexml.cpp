/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  �ļ�����: st_parsexml.cpp
 *  ��Ҫ����:
 *
 *  ��ǰ�汾:1.0
 *  ����: ��Ұ
 *  ����: 2015/08/11
 *  ˵��:
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

/* ȫ�������� */
extern struct ShadowTalkContext gCtx;

/**
*  ��������: ����xml keyvalue�����뵽cache��
*  @param  key keyֵ
*  @param  value valueֵ
*
*  @return 0 �ɹ�  -1 ʧ��
*/
static void addCacheForKeyValue(const QString key, const QString value) {
    std::string cKey = key.toStdString();
    std::string cValue = value.toStdString();

    std::string plainKey   = Base64::decode(cKey);
    std::string plainValue = Base64::decode(cValue);

    Cache *c = gCtx.cache;
    if (!c) {
        qDebug() << "[c++] : insert cache fail";
        return;
    }

    if (c->isExistChannel(cKey)){
        return;
    }

    c->insertKeyValue(plainKey,  plainValue);
    return;
}

/**
*  ��������: ����xml channel�����뵽cache��
*  @param  channelId      channel����
*  @param  createdTime    ����ʱ��
*  @param  expiredTime    ����ʱ��
*  @param  shortCode      ����
*
*  @return 0 �ɹ�  -1 ʧ��
*/
static void addCacheForChannel(
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
*  ��������: ����ϵ����Ϣ���뵽����
*  @param  defaultExpiredTime  Ĭ�ϳ�ʱʱ��
*  @param  friendChannelId     ����channel����
*  @param  inSession           �Ƿ��������б���
*  @param  friendName          ��������
*  @param  netStatus           ����״̬
*  @param  updateTime          ����ʱ��
*
*  @return 0 �ɹ�  -1 ʧ��
*/
static void addCacheForContact(
         QString &defaultExpiredTime,
         QString &friendChannelId,
         QString &inSession,
         QString &friendName,
         QString &netStatus,
         QString &updateTime)
{
    updateTime = updateTime;

    /* ����Ϊ�յ�ֱ�ӹ��˵� */
    if (friendName.isEmpty()) {
        return;
    }

    /* �������Ƿ��Ѿ����� */
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


    /* ���뻺�� */
    gCtx.cache->insertOneFriend(newOne);
    return;
}

static void addCacheForGroup(
        QString groupChannelId,
        QString localMemberId,
        QString gourpName,
        QString myNameInGroup,
        QString ownerID,
        QString showNotification,
        QString status)
{
    int status_ = status.toInt();
    if (status_ < 0) {
        return;
    }

    qDebug() << "[c++] : addCacheForGroup"
             << " groupChannelId - " << groupChannelId
             << " localMemberId - " << localMemberId
             << " gourpName - " << gourpName
             << " myNameInGroup - " << myNameInGroup
             << " ownerID - " << ownerID
             << " showNotification - " << showNotification
             << " status - " << status;

    /* ����Ϊ�յ�ֱ�ӹ��˵� */
    if (gourpName.isEmpty()) {
        return;
    }

    /* �������Ƿ��Ѿ����� */
    if (gCtx.cache->isExistGroup(groupChannelId)){
        return;
    }

    Group *newOne = new Group(groupChannelId, localMemberId, gourpName,
                myNameInGroup, ownerID, showNotification, gCtx.cache->getNextGroupIndex());
    if (!newOne) {
        return;
    }

    /* ���뻺�� */
    gCtx.cache->insertOneGroup(newOne);
    return;
}


static void addCacheForGroupMember(
         QString &memberId,
         QString &name,
         QString &status,
         QString &groupChannelId)
{
    int status_ = status.toInt();
    if (status_ < 0) {
        return;
    }

    qDebug() << "[c++] : addCacheForGroupMember"
             << " memberID - " << memberId
             << " name - " << name
             << " status - " << status
             << " groupChannelId - " << groupChannelId;

    /* �������Ƿ��Ѿ����� */
    if (gCtx.cache->isExistGroup(groupChannelId)){
        return;
    }

    /* �ҵ��� */
	Group *group = gCtx.cache->getOneGroup(groupChannelId);
    if (!group) {
        return;
    }
    /* ����Ա�Ƿ��Ѿ�����*/
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
*  ��������: ����xml����ϵ������Ԫ��
*  @param  array   ��ϵ���е�array��ǩԪ�ؽṹ
*
*  @return 0 �ɹ�  -1 ʧ��
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

    /* ���뻺�� */
    addCacheForContact(defaultExpiredTime, friendChannelId,
            inSession, friendName, netStatus, updateTime);

    return 0;
}

/**
*  ��������: ����xml����ϵ�˱�ǩԪ��
*  @param  dict  dict��ǩԪ��
*
*  @return 0 �ɹ�  -1 ʧ��
*/
int ParseXml::parseContactXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull(); dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++) {
        if (dict.isNull()) {
            qDebug() << "[c++] : can't find the dict child";
            return -1;
        } else {
            if (parseContactDict(dict) < 0) {
                return -1;
            }
        }
    }
//    walkCacheAddFriend();
    return 0;
}

/**
*  ��������: ����xml�� QrChannel�е�dict��ǩ
*  @param  dict   dict��ǩԪ��
*
*  @return 0 �ɹ�  -1 ʧ��
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

    /* ���뻺�� */
    addCacheForChannel(channelId, createdTime, expiredTime, shortCode);
    return 0;
}


/**
*  ��������: ����xml�ж�ά��channel��ǩ
*  @param  array   ��ά��channel�е�array��ǩԪ�ؽṹ
*
*  @return 0 �ɹ�  -1 ʧ��
*/
int ParseXml::parseQrChannelXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "[c++] : can't find the dict child";
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
*  ��������: ����xml�� keyValue�е�dict��ǩ
*  @param  dict   dict��ǩԪ��
*
*  @return 0 �ɹ�  -1 ʧ��
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

    /* ���뵽���� */
    addCacheForKeyValue(key, value);
    return 0;
}

/**
*  ��������: ����xml�е�array�µ���������
*  @param  array   keyvalue�е�array��ǩԪ�ؽṹ
*
*  @return 0 �ɹ�  -1 ʧ��
*/
int ParseXml::parseKeyValueXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "[c++] : can't find the dict child";
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
*  ��������: ����xml�е���ı�ǩ
*  @param  array   group�е�array��ǩԪ�ؽṹ
*
*  @return 0 �ɹ�  -1 ʧ��
*/
int ParseXml::parseGroupDict(QDomElement dict) {

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

    /* ���뻺�� */
    addCacheForGroup(groupChannelId, localMemberId, gourpName, myNameInGroup, ownerID,
                     showNotification, status);
    return 0;
}


/**
*  ��������: ����xml�е����Ա��ǩ
*  @param  array   group�е�array��ǩԪ�ؽṹ
*
*  @return 0 �ɹ�  -1 ʧ��
*/
int ParseXml::parseGroupXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "[c++] : can't find the dict child";
            return -1;
        } else {
            if (parseGroupDict(dict) < 0) {
                return -1;
            }
        }
    }
}


int ParseXml::parseGroupMemberDict(QDomElement dict) {
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

    /* ���뻺�� */
    addCacheForGroupMember(memberID, name, status, groupChannelId);
    return 0;

}

int ParseXml::parseGroupMemberXml(QDomElement &array) {
    QDomElement dict = array.firstChildElement(ST_XML_TAG_DICT);
    for (int i = 0; !dict.isNull();
         dict = dict.nextSiblingElement(ST_XML_TAG_DICT), i++)
    {
        if (dict.isNull()) {
            qDebug() << "[c++] : can't find the dict child";
            return -1;
        } else {
            if (parseGroupMemberDict(dict) < 0) {
                return -1;
            }
        }
    }
}



/**
*  ��������: дxml�����ļ�
*  @param  plainData  xml�ļ�����
*
*  @return ��
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


QString filterWords(const QString oldData) {
    std::string newData;
    std::string cppData = oldData.toStdString();
    unsigned long dataSize = cppData.size();

    char *cPtr = new char[dataSize];
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
*  ��������: ����xml�ļ���ں���
*  @param  plainData  xml�ļ�����
*
*  @return 0�ɹ�  -1ʧ��
*/
int ParseXml::parseDencryptXml(const QString plainData) {

    QDomDocument document;
    QString strError;
    int errLin = 0, errCol = 0;

    writeXmlFile(plainData);

    if (!document.setContent(plainData, false, &strError, &errLin, &errCol)) {
        qDebug() << "[c++] : parse file failed at line " << errLin << " column " << errCol << " " << strError;
        return -1;
    }

    if (document.isNull()) {
        qDebug() << "[c++] : document is null";
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
            qDebug() << "[c++] : can't find the array child";
            return -1;
        } else {
            array[i] = elt;
            arrayCount++;
        }
    }

    if (arrayCount < 3) {
        qDebug() << "[c++] : xml parse fail, array count is " << arrayCount;
        return -1;
    }

    /* �Ƚ����� */
    if (arrayCount >= 5) {
        if (parseGroupXml(array[3]) < 0) {
            return -1;
        }
        qDebug() << "[c++] : parse gourp success";

        if (parseGroupMemberXml(array[4]) < 0) {
            return -1;
        }
        qDebug() << "[c++] : parse group member success";
    }

    if (parseContactXml(array[0])  < 0) {
        return -1;
    }
    qDebug() << "[c++] : parse contact success";

    if (parseQrChannelXml(array[1]) < 0) {
        return -1;
    }
    qDebug() << "[c++] : parse qrchannel success";

    if (parseKeyValueXml(array[2]) < 0) {
        return -1;
    }
    qDebug() << "[c++] : parse keyvalue success";

    walkCacheAddFriendAndGroup();
    return 0;
}
