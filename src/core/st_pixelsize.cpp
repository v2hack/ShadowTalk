/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_pixelsize.cpp
 *  简要描述: 主要负责处理界面上文字和像素大小的相互转换
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include "st_pixelsize.h"
#include <QString>
#include <QDebug>
#include <QScreen>
#include <QFont>
#include <QFontMetricsF>
#include "st_context.h"


extern struct ShadowTalkContext gCtx;


/**
 *  功能描述: 像素大小转换构造函数
 *  @param index  好友索引
 *
 *  @return 无
 */
PointSizeToPixelSize::PointSizeToPixelSize(QObject *parent)
{
	parent = parent;
    return;
}

/**
 *  功能描述: 像素大小转换析构函数
 *  @param index  好友索引
 *
 *  @return 无
 */
PointSizeToPixelSize::~PointSizeToPixelSize()
{
    return;
}

/**
 *  功能描述: 像素点支持尺寸大小计算
 *  @param index  好友索引
 *
 *  @return 无
 */
int PointSizeToPixelSize::pixelSize(int pointSize)
{
    QScreen *screen = gCtx.app_->primaryScreen();
    if (!screen) {
        return 0;
    }
    int point_size = (pointSize * screen->logicalDotsPerInch()) / 75;
    return point_size;
}

/**
 *  功能描述: 计算界面文字高度
 *  @param pointSize  文字像素点
 *
 *  @return 无
 */
int PointSizeToPixelSize::height(int pointSize)
{
    QFont font = gCtx.app_->font();
    font.setPointSize(pointSize);
    QFontMetrics fm(font);
    return fm.height();
}

/**
 *  功能描述: c
 *  @param index  文字像素点
 *
 *  @return 无
 */
int PointSizeToPixelSize::width(int pointSize, QString text)
{
    QFont font = gCtx.app_->font();
    font.setPointSize(pointSize);
    QFontMetrics fm(font);
    return fm.width(text);
}
