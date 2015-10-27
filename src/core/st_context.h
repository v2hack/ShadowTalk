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
    peersafe::im::Message_client *zebra_;   /* peersafe底层类指针 */
    zebraDeleagates *delegate_;             /* peersafe回调类指针 */
    struct ShadowTalkConfig conf;           /* 配置结构 */

    QGuiApplication *app_;                  /* application 指针*/
    QQuickView      *viewer_;               /* 主窗口viewer指针 */
    QQuickView      *loginer_;              /* 登陆窗口viewer指针 */
    QQuickView      *imager_;               /* 图片浏览窗口指针 */
    TrayIcon        *tray_;                 /* 系统托图 */

    Cache *cache;                           /* 缓存指针 */
    std::string phoneQrChannel;             /* 与手机同步的qr channel id*/
    std::string phoneSyncChannel;           /* 与手机同步的normal channel id*/
    QTime phoneUpdateTime;                  /* 手机刷新时间 */

    int changeFlag_;                        /* 窗口切换标记 */
    int windowFlag_;                        /* 窗口编号 */
    int threadStop_;                        /* 线程状态 */
    int loadXmlFlag_;                       /* 加载xml文件状态 */
};

/* 检查声音快关 */
bool isSoundEnable();

/* 检查接受消息的开关*/
bool isReceiveEnable();

/* 设置声音的开关 */
void setSoundEnable(bool set);

/* 设置接收消息开关 */
void setReceiveEnable(bool set);


#endif // CONTEXT_H
