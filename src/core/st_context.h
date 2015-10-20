#ifndef CONTEXT_H
#define CONTEXT_H

#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml>
#include <QTime>

#include "st_friend.h"
#include "st_cache.h"
#include "st_zebra.h"
#include "st_trayicon.h"

#include "im.h"


enum shadowTalkFlag
{
    ST_NO_LOGIN = 0,        /* 没有登录状态 */
    ST_ALREADY_LONIN = 1,   /* 已经登录状态 */
};


/* 配置结构 */
struct ShadowTalkConfig
{
    bool soundEnable;   /* 声音开关 */
    bool reciveEnable;  /* 消息接收开关 */
};

/* 全局上下文索引 */
struct ShadowTalkContext
{
    peersafe::im::Message_client *zebra;   /* peersafe底层类指针 */
    zebraDeleagates *delegate;             /* peersafe回调类指针 */
    struct ShadowTalkConfig conf;          /* 配置结构 */

    QGuiApplication *app;                  /* application 指针*/
    QQuickView      *viewer;               /* 主窗口viewer指针 */
    QQuickView      *loginer;              /* 登陆窗口viewer指针 */
    QQuickView      *imager;               /* 图片浏览窗口指针 */
    TrayIcon        *tray;                 /* 系统托图 */

    Cache *cache;                          /* 缓存指针 */
    std::string phoneQrChannel;            /* 与手机同步的qr channel id*/
    std::string phoneSyncChannel;          /* 与手机同步的normal channel id*/
    QTime phoneUpdateTime;                 /* 手机刷新时间 */

    int changeFlag;                        /* 窗口切换标记 */
    int windowFlag;                        /* 窗口编号 */
    int shadowFlag;                        /* 软件状态 */
    int threadStop;
};


bool isSoundEnable();
bool isReceiveEnable();
void setSoundEnable(bool set);
void setReceiveEnable(bool set);


#endif // CONTEXT_H
