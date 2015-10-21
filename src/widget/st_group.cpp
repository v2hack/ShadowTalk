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
#include "st_group.h"
#include "st_context.h"
#include "st_log.h"
#include "st_message.h"
#include "st_utils.h"
#include "st_chat.h"
#include "st_cache.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

Group::Group(QString groupChannelId, QString localMemberId, QString gourpName,
             QString myNameInGroup, QString ownerID, QString showNotification, int groupId) {
    groupChannelId_     = groupChannelId;
    localMemberId_      = localMemberId;
    gourpName_          = gourpName;
    myNameInGroup_      = myNameInGroup;
    ownerID_            = ownerID;
    showNotification_   = showNotification;
    gid_                = groupId;
    messageUnreadCount_ = 0;
}

Group::~Group() {

}

void Group::insertOneMessage(GroupMessage *message) {
    this->messageList_.insert(this->messageList_.size(), *message);
    return;
}

void Group::insertOneMember(QString &memberId, QString &name) {
    this->memberList_.insert(memberId, name);
    return;
}

bool Group::isExistMember(QString &memberId) {
    QMap<QString, QString>::iterator it;
    it = this->memberList_.find(memberId);
    if (it == this->memberList_.end()) {
        return false;
    }
    return true;
}


/**
 *  功能描述: 设置friendlistView中的item背景色为透明
 *
 *  @return 无
 */
void Group::setFriendlistBackGroundColor(int colorFlag) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "modifyBackColor",
                    Q_ARG(QVariant, listViewIndex_),
                    Q_ARG(QVariant, colorFlag));
    }
    return;
}

/**
 *  功能描述: 设置chatlistView中的item背景色为透明
 *
 *  @return 无
 */
void Group::setChatlistBackGroundColor(int colorFlag, int chatListIndex) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("ChatListModel");
    if (rect) {
        QMetaObject::invokeMethod(
                    rect,
                    "modifyBackColor",
                    Q_ARG(QVariant, chatListIndex),
                    Q_ARG(QVariant, colorFlag));
    }
    return;
}

/**
 *  功能描述: SelectFriend构造函数
 *  @return 无
 */
SelectGroup::SelectGroup(QObject *parent) {
	parent = parent;

}

/**
 *  功能描述: SelectFriend的析构函数
 *  @return 无
 */
SelectGroup::~SelectGroup() {

}


void SelectGroup::refreshGroupMessage(Group *g)
{
    /* 添加消息 */
    for (int i = 0; i < g->messageList_.size(); i++) {
        int idx = i;
        QMap<int, GroupMessage>::iterator it = g->messageList_.find(i);
        if (it == g->messageList_.end()) {
            return;
        }

        /* 设置显示名字 */
        QString name;
        if (it->driect == MessageDriectMe) {
            name = "Me";
        } else {
            name = QString::fromStdString(it->senderName);
        }

        /* 添加消息到界面 */
        switch (it->messageType) {
        case MessageTypeWord:
            MessageWidget::addMessageToWidget(g->gid_, name, it->messageType,
                               it->driect, QString::fromStdString(it->data), idx);
            break;
        case MessageTypeImage:
            MessageWidget::addImageToWidget(g->gid_, name, it->messageType,
                             it->driect, it->data, idx);
            break;
        case MessageTypeVoice:
            MessageWidget::addVoiceToWidget(g->gid_, name, it->messageType, it->driect,
                             QString::fromStdString(it->data), it->voiceSeconds, idx);
            break;
        default:
            break;
        }
    }
    return;
}

void SelectGroup::refreshGroupStatistics(Group *g)
{
    /* 界面显示清零 */
    Utils::displayCurrentFriendName(g->gourpName_);
    /* 未读消息计数清零 */
    Chat::displayChatUnreadCount(g->gid_, 0);
    g->messageUnreadCount_ = 0;
    return;
}

/**
 *  功能描述: 改变界面上的消息列表
 *  @param index 好友索引
 *  @param name 好友名称
 *  @return 无
 */
void SelectGroup::changeMessageListForFlist(int groupCacheIndex, QString name)
{
    qDebug() << "c++: group changeMessageListForFlist cacheIndex - "
             << groupCacheIndex << " name - " << name;

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    /* 找到好友缓存 */
	Group *g = c->getOneGroup(groupCacheIndex);
    if (!g) {
        return;
    }

    /* 清理界面消息 */
    MessageWidget::clearMessageFromWidget();
    this->refreshGroupMessage(g);
    this->refreshGroupStatistics(g);
    Utils::clearCurrentItemHighLight(c);
    c->setCurrentId(groupCacheIndex, CHATITEM_TYPE_GROUP, name);
    Utils::setGroupItemHighLight(c, g, groupCacheIndex);
    qDebug() << "\n";
    return;
}

void SelectGroup::changeMessageListForClist(int groupCacheIndex, QString name)
{
    qDebug() << "c++: group changeMessageListForClist cacheIndex - "
             << groupCacheIndex  << " name - " << name;;

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    /* 找到好友缓存 */
    Group *g = c->getOneGroup(groupCacheIndex);
    if (!g) {
        return;
    }
    /* 清理界面消息 */
    MessageWidget::clearMessageFromWidget();
    this->refreshGroupMessage(g);
    this->refreshGroupStatistics(g);
    Utils::clearCurrentItemHighLight(c);
    c->setCurrentId(groupCacheIndex, CHATITEM_TYPE_GROUP, name);
    Utils::setGroupItemHighLight(c, g, groupCacheIndex);
    qDebug() << "\n";
    return;
}

