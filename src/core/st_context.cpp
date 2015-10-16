
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
bool isSoundEnable() {
    return gCtx.conf.soundEnable;
}

/**
 *  功能描述: 检查接受消息的开关
 *  @param 无
 *
 *  @return 无
 */
bool isReceiveEnable() {
    return gCtx.conf.reciveEnable;
}

/**
 *  功能描述: 设置声音的开关
 *  @param 无
 *
 *  @return 无
 */
void setSoundEnable(bool set) {
    gCtx.conf.soundEnable = set;
}

/**
 *  功能描述: 设置接收消息开关
 *  @param 无
 *
 *  @return 无
 */
void setReceiveEnable(bool set) {
    gCtx.conf.reciveEnable = set;
}
