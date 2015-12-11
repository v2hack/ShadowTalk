/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_thread.cpp
 *  简要描述: 主要负责显示搜索的匹配窗口、登录和主窗口的切换
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <iostream>
#include "st_thread.h"
#include "st_utils.h"
#include "st_net.h"

Sthread::Sthread(struct ShadowTalkContext *ctx, QObject *parent)
{
    parent = parent;
    c = ctx;
}

void Sthread::run()
{
    while (1) {
        if (c->threadStop_ == 1) {
            break;
        }

        /* 登录界面切换检查 */
        if (c->changeFlag_ == 1) {
            if (c->windowFlag_ == 1) {
                qDebug() << "c++: show login";
                c->loginer_->show();
                c->viewer_->close();
            } else if (c->windowFlag_ == 2) {
                qDebug() << "c++: show main";
                c->loginer_->close();
                c->viewer_->show();
            }
            c->changeFlag_ = 0;
        } else {
            Utils::ShadowTalkSleep(1000);
        }
    }
}


Listenthread::Listenthread(struct ShadowTalkContext *ctx, QObject *parent)
{
    parent = parent;
    context = ctx;
}

void Listenthread::run()
{
    /* 监听好友 */
    Adapt::adaptListenAllFriends();
    /* 监听组 */
    Adapt::adaptListenAllGroups();
    return;
}
