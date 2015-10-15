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
    groupChannelId_   = groupChannelId;
    localMemberId_    = localMemberId;
    gourpName_        = gourpName;
    myNameInGroup_    = myNameInGroup;
    ownerID_          = ownerID;
    showNotification_ = showNotification;
	gid_ = groupId;
}

Group::~Group() {

}

void Group::insertOneMessage(GroupMessage *message) {
    this->messageList.insert(this->messageList.size(), *message);
    return;
}

void Group::insertOneMember(QString &memberId, QString &name) {
    this->memberList.insert(memberId, name);
    return;
}

bool Group::isExistMember(QString &memberId) {
    QMap<QString, QString>::iterator it;
    it = this->memberList.find(memberId);
	if (it == this->memberList.end()) {
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
                    Q_ARG(QVariant, listViewIndex),
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

}


/**
 *  功能描述: SelectFriend的析构函数
 *  @return 无
 */
SelectGroup::~SelectGroup() {

}

/**
 *  功能描述: 改变界面上的消息列表
 *  @param index 好友索引
 *  @param name 好友名称
 *  @return 无
 */
void SelectGroup::changeMessageListForGroup(int index, QString name) {
    qDebug() << "changeMessageListForGroup index - " << index;
    /* 清理界面消息 */
    clearMessageFromWidget();

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        return;
    }

    /* 找到好友缓存 */
    Group *g = c->getOneGroup(index);
    if (!g) {
        return;
    }

    /* 添加消息 */
    for (int i = 0; i < g->messageList.size(); i++) {
        int idx = i;
        QMap<int, GroupMessage>::iterator it = g->messageList.find(i);
        if (it == g->messageList.end()) {
            return;
        }

        /* 设置显示名字 */
        QString name;
        if (it->driect == MessageDriectMe) {
            name = "Me";
        } else {
            name.fromStdString(it->senderName);
        }

        /* 添加消息到界面 */
        switch (it->messageType) {
        case MessageTypeWord:
            addMessageToWidget(g->gid_, name, it->messageType,
                               it->driect, QString::fromStdString(it->data), idx);
            break;
        case MessageTypeImage:
            addImageToWidget(g->gid_, name, it->messageType,
                             it->driect, it->data, idx);
            break;
        case MessageTypeVoice:
            addVoiceToWidget(g->gid_, name, it->messageType, it->driect,
                             QString::fromStdString(it->data), it->voiceSeconds, idx);
            break;
        default:
            break;
        }
    }

    /* 界面显示清零 */
    displayCurrentFriendName(g->gourpName_);
    /* 未读消息计数清零 */
    displayChatUnreadCount(g->gid_, 0);
    g->messageUnreadCount = 0;

    /* 上次选中的取消高亮 */
    Group *old_group = c->getOneGroup(c->currentUseId);
    if (old_group) {
        qDebug() << "[c++] : find one old_group, and set back color - " << old_group->listViewIndex;
        old_group->setFriendlistBackGroundColor(0);
        int chatListSeq_old = c->getPositionNum(c->currentUseId);
        if (chatListSeq_old >= 0) {
            old_group->setChatlistBackGroundColor(0, chatListSeq_old);
        }
    } else {
        qDebug() << "[c++] : can't friend old_group - " << c->currentUseId;
    }
    /* 当前选中的高亮 */
    int chatListSeq_new = c->getPositionNum(index);
    if (chatListSeq_new >= 0) {
        g->setChatlistBackGroundColor(1, chatListSeq_new);
    }

    /* 当前选中的高亮 */
    g->setFriendlistBackGroundColor(1);
    /* 设置新的当前好友item */
    c->setCurrentId(index, 1);

    /* 以下操作检查是否需要在chat页面显示好友 */
    int ret = c->atFirstPosition(index);
    if (ret == -1) {
        c->insertOneChat(index, g->gourpName_);
    }/* else if (ret == -2) {
        c->removeOneChat(index);
        c->insertOneChat(index, f->name);
    }*/
    return;
}
