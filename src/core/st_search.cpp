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

int checkSearchText()
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return 0;
    }

    QVariant isEmptyText;
    isEmptyText.fromValue(0);

    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "searchTextIsEmpty",
                    Qt::DirectConnection,
                    Q_RETURN_ARG(QVariant, isEmptyText));
        if (ret == false) {
            qDebug() << "invokeMethod (searchTextIsEmpty) fail";
        }
    }
    return isEmptyText.toInt();
}


void setSearchTextUnvisible()
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "setSearchUnvisible",
                    Qt::DirectConnection);
        if (ret == false) {
            qDebug() << "invokeMethod (setSearchUnvisible) fail";
        }
    }
}

void setSearchTextVisible()
{
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "setSearchVisible",
                    Qt::DirectConnection);
        if (ret == false) {
            qDebug() << "invokeMethod (setSearchTextVisible) fail";
        }
    }
}


QString getSearchTextContent() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return "";
    }

    QVariant text;
    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "searchTextContent",
                    Qt::DirectConnection,
                    Q_RETURN_ARG(QVariant, text));
        if (ret == false) {
            qDebug() << "invokeMethod (searchTextContent) fail";
        }
    }
    return text.toString();
}


void addSearchResultWidget(QString friendName, int friendIndex) {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement;
    newElement.insert("friendName",  friendName);
    newElement.insert("friendIndex", friendIndex);

    QObject *rect = rootObject->findChild<QObject*>("SearchListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "addFriend",
                    Q_ARG(QVariant, QVariant::fromValue(newElement)));
        if (ret == false) {
            qDebug() << "invokeMethod (addSearchResultWidget) fail";
        }
    }
}

void clearSearchWidget() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("SearchListModel");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "clearFriend");
        if (ret == false) {
            qDebug() << "invokeMethod (clearSearchWidget) fail";
        }
    }
}


bool matchSearchContent(QString text) {

    bool ret = false;
    Cache *c = gCtx.cache;
    if (!c) {
        return ret;
    }

    QMap<int, Friend>::iterator it;
    for (it = c->friendList.begin(); it != c->friendList.end(); it++) {
        Friend &f = it.value();
        if (f.name.indexOf(text) != -1) {
            ret = true;
            addSearchResultWidget(f.name, f.id);
        }
    }
    return ret;
}


void clearSearchContent() {
    QQuickItem *rootObject = gCtx.viewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariant text;
    QObject *rect = rootObject->findChild<QObject*>("SearchTextEdit");
    if (rect) {
        bool ret = QMetaObject::invokeMethod(
                    rect,
                    "searchClearContent",
                    Qt::DirectConnection);
        if (ret == false) {
            qDebug() << "invokeMethod (searchClearContent) fail";
        }
    }
    return;
}

static QString searchText;


void matchAndShowSearchResult() {
    QString text = getSearchTextContent();
    if (text.isEmpty()) {
        return;
    }

    if (searchText.indexOf(text) == -1) {
        if (matchSearchContent(text)) {
            setSearchTextVisible();
        }
        searchText = text;
    }
}
