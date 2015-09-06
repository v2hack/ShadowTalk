#ifndef CONTEXT_H
#define CONTEXT_H

#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml>

#include "st_friend.h"
#include "st_cache.h"
#include "st_zebra.h"

#include "im.h"

/* 配置结构 */
struct ShadowTalkConfig {
    bool soundEnable;   /* 声音开关 */
    bool reciveEnable;  /* 消息接收开关 */
};

/* 全局上下文索引 */
struct ShadowTalkContext
{
    QGuiApplication *app;  /* application 指针*/

    QQuickView *viewer;    /* 主窗口viewer指针 */
    QQuickView *loginer;   /* 登陆窗口viewer指针 */
    QQuickView *imager;    /* 图片浏览窗口指针 */

    Cache *cache;          /* 缓存指针 */

    peersafe::im::Message_client *zebra;
    zebraDeleagates *delegate;

    std::string phoneQrChannel;   /* 与手机同步的qr channel id*/
    std::string phoneSyncChannel; /* 与手机同步的normal channel id*/

    struct ShadowTalkConfig conf; /* 配置结构 */

    int changeFlag;
    int windowFlag;
};

bool isSoundEnable();
bool isReceiveEnable();
void setSoundEnable(bool set);
void setReceiveEnable(bool set);


#endif // CONTEXT_H
