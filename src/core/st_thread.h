#ifndef STHREAD_H
#define STHREAD_H


#include <QThread>
#include <QDebug>

#include "st_context.h"
#include "st_cache.h"
#include "st_utils.h"

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
            qDebug() << "check to change windows";
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
