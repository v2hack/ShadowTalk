#ifndef STHREAD_H
#define STHREAD_H

#include <QThread>
#include <QDebug>

#include "st_context.h"
#include "st_cache.h"
#include "st_utils.h"
#include "st_search.h"


class Sthread : public QThread
{
    Q_OBJECT
public:
    struct ShadowTalkContext *c;

    explicit Sthread(struct ShadowTalkContext *ctx, QObject *parent = 0) {
        c = ctx;
    }
    void run() {
        while (1) {
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
};

#endif // STHREAD_H
