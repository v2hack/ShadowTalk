
#include <QString>

#include "st_context.h"

/* 全局上下文 */
extern struct ShadowTalkContext gCtx;

bool isSoundEnable() {
    return gCtx.conf.soundEnable;
}

bool isReceiveEnable() {
    return gCtx.conf.reciveEnable;
}

void setSoundEnable(bool set) {
    gCtx.conf.soundEnable = set;
}

void setReceiveEnable(bool set) {
    gCtx.conf.reciveEnable = set;
}
