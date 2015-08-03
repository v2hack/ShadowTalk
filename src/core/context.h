#ifndef CONTEXT_H
#define CONTEXT_H

#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml>

#include "friend.h"
#include "cache.h"


/* 全局上下文索引 */
struct ShadowTalkContext
{
    QGuiApplication *app;  /* application 指针*/
    QQuickView *viewer;    /* 主窗口viewer指针 */
    QQuickView *loginer;   /* 登陆窗口viewer指针 */
    Cache *cache;          /* 缓存指针 */
};

#endif // CONTEXT_H
