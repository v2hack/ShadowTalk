/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称:
 *  简要描述:
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include "pixelsize.h"
#include <QString>
#include <QDebug>
#include <QScreen>
#include <QFont>
#include <QFontMetricsF>
#include "context.h"


extern struct ShadowTalkContext gCtx;

PointSizeToPixelSize::PointSizeToPixelSize(QObject *parent) {
    return;
}

PointSizeToPixelSize::~PointSizeToPixelSize() {
    return;
}


int PointSizeToPixelSize::pixelSize(int pointSize) {
    QScreen *screen = gCtx.app->primaryScreen();
    if (!screen) {
        return 0;
    }
    int point_size = (pointSize * screen->logicalDotsPerInch()) / 75;
    return point_size;
}

int PointSizeToPixelSize::height(int pointSize) {
    QFont font = gCtx.app->font();
    font.setPointSize(pointSize);
    QFontMetrics fm(font);
    return fm.height();
}

int PointSizeToPixelSize::width(int pointSize, QString text) {
    QFont font = gCtx.app->font();
    font.setPointSize(pointSize);
    QFontMetrics fm(font);
    return fm.width(text);
}
