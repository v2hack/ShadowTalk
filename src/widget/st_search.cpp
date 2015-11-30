/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_search.cpp
 *  简要描述: 主要负责搜索联系人及组
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <QWidget>
#include <QtQuick/QQuickView>
#include <QDateTime>
#include <stdio.h>
#include <stdlib.h>
#include "st_chat.h"
#include "st_friend.h"
#include "st_context.h"
#include "st_log.h"
#include "st_message.h"
#include "st_utils.h"
#include "st_cache.h"
#include "st_search.h"

extern struct ShadowTalkContext gCtx;

/* 用户保存搜寻输入的内容 */
static QString searchText;

/**
 *  功能描述: 检测搜寻输入框的内容是否为空
 *  @param  无
 *
 *  @return 返回输入框字符数量
 */
int Search::checkSearchText()
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return 0;
    }

    QVariant isEmptyText;
    isEmptyText.fromValue(0);

    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "searchTextIsEmpty",
                    Qt::DirectConnection, Q_RETURN_ARG(QVariant, isEmptyText));
        if (ret == false) {
            qDebug() << "c++: invokeMethod (searchTextIsEmpty) fail";
        }
    }
    return isEmptyText.toInt();
}

/**
 *  功能描述: 设置搜寻结果框不可见
 *  @param  无
 *
 *  @return 无
 */
void Search::setSearchTextUnvisible()
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "setSearchUnvisible", Qt::DirectConnection);
        if (ret == false) {
            qDebug() << "c++: invokeMethod (setSearchUnvisible) fail";
        }
    }
    return;
}

void LoadAllToWidget()
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return;
    }

    qDebug()<<"c++: invokeMethod LoadAllToWidget  add by hsf";

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect,"loadallFriend",Qt::DirectConnection);
        if (ret == false) {
            qDebug() << "c++: invokeMethod (addSearchResultWidget) fail";
        }
    }
    return;
}

/**
 *  功能描述: 设置搜寻结果框可见
 *  @param  无
 *
 *  @return 无
 */
void setSearchTextVisible()
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "setSearchVisible", Qt::DirectConnection);
        if (ret == false) {
            qDebug() << "c++: invokeMethod (setSearchTextVisible) fail";
        }
    }
    return;
}

/**
 *  功能描述: 获取搜索输入框内容
 *  @param  无
 *
 *  @return 返回搜索关键字
 */
QString getSearchTextContent()
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return "";
    }

    QVariant text;
    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "searchTextContent",
                    Qt::DirectConnection, Q_RETURN_ARG(QVariant, text));
        if (ret == false) {
            qDebug() << "c++: invokeMethod (searchTextContent) fail";
        }
    }
    return text.toString();
}

/**
 *  功能描述: 根据搜索结果显示在search listview上
 *  @param  friendName    好友名
 *  @param  friendIndex   好友索引
 *
 *  @return 无
 */
void addSearchResultWidget(QString friendName, int friendIndex)
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    newElement.insert("friendName",  friendName);
    newElement.insert("friendIndex", friendIndex);

    QObject *rect = rootObject->findChild<QObject*>("SearchListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect,"addFriend",
                    Q_ARG(QVariant, QVariant::fromValue(newElement)));
        if (ret == false) {
            qDebug() << "c++: invokeMethod (addSearchResultWidget) fail";
        }
    }
    return;
}

/**
 *  功能描述: 清理search listview中的内容
 *  @param 无
 *
 *  @return 无
 */
void Search::clearSearchWidget()
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("SearchListModel");
    if (rect) {
         bool ret = QMetaObject::invokeMethod(rect, "clearFriend");
        if (ret == false) {
            qDebug() << "c++: invokeMethod (clearSearchWidget) fail";
        }
    }
    return;
}

/**
 *  功能描述: 根据搜索结果显示在search listview上
 *  @param  friendName    好友名
 *  @param  friendIndex   好友索引
 *
 *  @return 无
 */
void SearchResultWidget(QString friendName)
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return;
    }

    qDebug()<<"c++: SearchResultWidget invokeMethod ,friendName is "+friendName;

    QObject *rect = rootObject->findChild<QObject*>("FriendListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect,"searchFriend",
                    Q_ARG(QVariant, QVariant::fromValue(friendName)));
        if (ret == false) {
            qDebug() << "c++: invokeMethod (addSearchResultWidget) fail";
        }
    }
    return;
}

/**
 *  功能描述: 根据输入关键字进行匹配
 *  @param  text 关键字
 *
 *  @return 匹配上返回true  没有匹配结果返回false
 */
bool matchSearchContent(QString text)
{
    bool ret = false;
    Cache *c = gCtx.cache;
    if (!c) {
        return ret;
    } 
    //add by hsf 2015年11月12日10:31:53
    SearchResultWidget(text);

    /*close by hsf 2015年11月12日10:31:22
    QMap<int, Friend>::iterator it;
    for (it = c->friendList_.begin(); it != c->friendList_.end(); it++) {
        Friend &f = it.value();
        if (f.name_.indexOf(text) != -1) {
            ret = true;
            addSearchResultWidget(f.name_, f.cacheIndex_);
        }
    }
    */
    return ret;
}

/**
 *  功能描述: 清理搜索输入框的内容
 *  @param  无
 *
 *  @return 无
 */
void clearSearchContent()
{
    QQuickItem *rootObject = gCtx.viewer_->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(rect, "searchClearContent", Qt::DirectConnection);
        if (ret == false) {
            qDebug() << "c++: invokeMethod (searchClearContent) fail";
        }
    }
    return;
}

/**
 *  功能描述: 匹配并显示搜索结果
 *
 *  @return 无
 */
void Search::matchAndShowSearchResult()
{
    QString text = getSearchTextContent();
    if (text.trimmed().isEmpty() || text.trimmed().isNull() ||text.trimmed()=="") {
        qDebug() << "c++ Search::matchAndShowSearchResult,Empty ,begin to LoadAllToWidget";
        LoadAllToWidget();
        return;
    }

    if (searchText.indexOf(text) == -1) {
        if (matchSearchContent(text)) {
            //setSearchTextVisible();
        }
        searchText = text;
    }
    return;
}


GoSearch::GoSearch(QObject *parent) {
    parent = parent;

}

/**
 *  功能描述: 匹配并显示搜索结果
 *  对好友列表进行搜索，采用model的过滤
 *  hsf 2015-11-3
 *  @return
 */
GoSearch::~GoSearch() {

}

void GoSearch::goSearchFriend(QString name)
{
    qDebug() <<"goSearchFriend---name:"<<name;
    if (matchSearchContent(name)){
        qDebug()<<"c++ load goSearchFriend success...";
    }
}

/**
 *  功能描述: 匹配并显示搜索结果
 *  加载全部好友
 *  hsf 2015-11-3
 *  @return
 */
void GoSearch::goLoadAllFriend()
{
    LoadAllToWidget();
}
