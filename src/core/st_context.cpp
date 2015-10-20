/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_context.h
 *  简要描述: 程序上下文管理接口，主要处理程序的配置及设置
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <QString>
#include "st_context.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 检查声音快关
 *  @param 无
 *
 *  @return 无
 */
bool isSoundEnable()
{
    return gCtx.conf.soundEnable;
}

/**
 *  功能描述: 检查接受消息的开关
 *  @param 无
 *
 *  @return 无
 */
bool isReceiveEnable()
{
    return gCtx.conf.reciveEnable;
}

/**
 *  功能描述: 设置声音的开关
 *  @param 无
 *
 *  @return 无
 */
void setSoundEnable(bool set)
{
    gCtx.conf.soundEnable = set;
}

/**
 *  功能描述: 设置接收消息开关
 *  @param 无
 *
 *  @return 无
 */
void setReceiveEnable(bool set)
{
    gCtx.conf.reciveEnable = set;
}
