#include "st_thread.h"

Sthread::Sthread(struct ShadowTalkContext *ctx, QObject *parent) {
    parent = parent;
    c = ctx;
}

void Sthread::run() {
    while (1) {
        if (c->threadStop == 1) {
            break;
        }
        /* 搜索框检查 */
        if (checkSearchText() == 1) {
            setSearchTextUnvisible();
            clearSearchWidget();
        } else {
            matchAndShowSearchResult();
        }

        /* 登录界面切换检查 */
        if (c->changeFlag == 1) {
            if (c->windowFlag == 1) {
                qDebug() << "show login";
                c->loginer->show();
                c->viewer->close();
            } else if (c->windowFlag == 2) {
                qDebug() << "show main";
                c->loginer->close();
                c->viewer->show();
            }
            c->changeFlag = 0;
        } else {
            ShadowTalkSleep(1000);
        }
    }
}
