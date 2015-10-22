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
    explicit Sthread(struct ShadowTalkContext *ctx, QObject *parent = 0);
    void run();
};


#endif // STHREAD_H
