/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_picture.cpp
 *  简要描述: 主要处理图片的缩放、裁剪、显示及生成文件
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/08/11
 *  说明:
 ******************************************************************/
#include <QMap>
#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QString>
#include <QQuickView>
#include <fstream>
#include <string>
#include "st_utils.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_message.h"
#include "st_picture.h"
#include "st_context.h"
#include "st_cache.h"

/* 全局上下文结构 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: 将图片生成为文件
 *  @param  fileName 文件名
 *  @param  data     图片数据
 *
 *  @return 无
 */
void NormalPicture::writePictureFile(std::string fileName, std::string data)
{
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::binary);
    file.write(data.c_str(), data.size());
    file.close();
    return;
}

/**
 *  功能描述: 查找图片缓存
 *  @param  fidx  好友id
 *  @param  midx  消息id
 *
 *  @return 返回图片数据内容
 */
std::string NormalPicture::findPictureCache(QString fidx, QString midx)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return std::string("");
    }

    if (c->currentUseType_ == CHATITEM_TYPE_FRIEND) {
        Friend *f = c->getOneFriend(fidx.toInt());
        if (!f) {
            qDebug() << "[c++] : can't find friend index - " << fidx;
            return std::string("");
        }

        /* 如果是音频消息则返回内容 */
        QMap<int, Message>::iterator it = f->messageList.find(midx.toInt());
        if (it != f->messageList.end()) {
            Message &m = it.value();
            if (m.messageType == MessageTypeImage) {
                return m.data;
            }
        }
        qDebug() << "[c++] : friend findPictureCache - can't find image message - fid:"
                 << fidx << " mid:" << midx;
        return std::string("");
    } else {
        Group *g = c->getOneGroup(fidx.toInt());
        if (!g) {
            qDebug() << "[c++] : can't find group index - " << fidx;
            return std::string("");
        }

        /* 如果是音频消息则返回内容 */
        QMap<int, GroupMessage>::iterator it = g->messageList_.find(midx.toInt());
        if (it != g->messageList_.end()) {
            GroupMessage &m = it.value();
            if (m.messageType == MessageTypeImage) {
                return m.data;
            }
        }
        qDebug() << "[c++] : group findPictureCache - can't find image message - fid:"
                 << fidx << " mid:" << midx;
        return std::string("");
    }
    return std::string("");
}

/**
 *  功能描述: 将文件持久化，并返回文件的存放路径
 *  @param  fidx  好友id
 *  @param  midx  消息id
 *  @param  pictureData 图片数据
 *
 *  @return 返回图片数据内容
 */
QUrl NormalPicture::displayPicture(QString fidx, QString midx, std::string pictureData)
{
    /* 组装文件路径及名字 */
    QString tempFilePath = QString("%0%1-%2%3").arg(SHADOWTALK_TEMP_DIR, fidx, midx, SHADOWTALK_IMAGE_PREFIX);
    std::string friendPictureFile = tempFilePath.toStdString();
    NormalPicture::writePictureFile(friendPictureFile, pictureData);
    /* 拼装文件绝对路径，并设置qml播放的source属性 */
    QString tempPath = QString("%0%1%2-%3%4").arg(QGuiApplication::applicationDirPath(),
                                                  "/temp/", fidx, midx, SHADOWTALK_IMAGE_PREFIX);
    const QUrl pictureUrl = QUrl::fromLocalFile(tempPath);
    return pictureUrl;
}

/**
 *  功能描述: 缩放图片计算
 *  @param  filePath  文件路径
 *  @param  height    返回的文件高度
 *  @param  width     返回的文件宽度
 *  @param  limit     文件高和管的上限
 *
 *  @return 返回0 -1
 */
int NormalPicture::shrinkPicture(QString filePath, int &height, int &width, int limit)
{
    double times = 0;
    QImage image;

    /* 计算图片的高和宽 */
    if (!image.load(filePath)) {
        qDebug() << "open image fail";
        return -1;
    }
    QPixmap pix = QPixmap::fromImage(image);

    /* 高度缩放 */
    if (pix.height() > limit) {
        times  =  (double)limit / (double)pix.height();
        height = (double)pix.height() * times;
        width  = (double)pix.width() * times;
    } else {
        height = pix.height();
        width = pix.width();
    }

    if (width > limit) {
        times  = (double)limit / (double)pix.width();
        height = (double)height * times;
        width  = (double)width * times;
    }
    return 0;
}

/**
 *  功能描述: 显示文件的构造函数
 *  @param  parent 父类
 *
 *  @return 返回0 -1
 */
NormalPicture::NormalPicture(QObject *parent) : QObject(parent) {}

/**
 *  功能描述: 设置显示大图的显示框
 *  @param  viewer 显示大区的viewer
 *  @param  viewer qml属性
 *  @param  viewer qml文件路径
 *
 *  @return 返回0 -1
 */
static void setViewerParameter(QQuickView &viewer, QString qmlProperty, QString qmlFile)
{
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(qmlFile));

    /* 设置无边框及透明 */
    viewer.setFlags(Qt::FramelessWindowHint | Qt::Window);
    viewer.setColor(QColor(Qt::transparent));

    /* viewer注册到qml */
    QQmlContext *qmlContext = viewer.rootContext();
    if (qmlContext) {
        qmlContext->setContextProperty(qmlProperty, &viewer);
    }
    return;
}

/**
 *  功能描述: 设置显示大图
 *  @param  friendIndex  好友索引
 *  @param  messageIndex 消息索引
 *
 *  @return 无
 */
void NormalPicture::displayNormalPicture(QString friendIndex, QString messageIndex)
{
    if (gCtx.imager == NULL) {
        gCtx.imager = new QQuickView;
    }
    setViewerParameter(*gCtx.imager, "pictureWindow", "qrc:/qml/picture.qml");

    std::string fileData = NormalPicture::findPictureCache(friendIndex, messageIndex);
    if (fileData.empty()) {
        qDebug() << "[c++] : normal picture is empty";
        return;
    }
    /* 持久化图片文件 */
    QUrl picturePath = NormalPicture::displayPicture(friendIndex, messageIndex, fileData);
    if (picturePath.isEmpty()) {
        return;
    }

    int height = 0, width = 0;
    if (NormalPicture::shrinkPicture(picturePath.toLocalFile(), height, width, 600) < 0) {
        qDebug() << "[c++] : shrink picture fail";
        return;
    }

    /* 添加qml对象属性 */
    QQuickItem *rootObject = gCtx.imager->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("qmlNormalImage");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setPicture", Q_ARG(QVariant, picturePath.toString()),
                                  Q_ARG(QVariant, height), Q_ARG(QVariant, width));
        qDebug() << "[c++] : insert one picture ok";
    } else {
        qDebug() << "[c++] : insert one picture fail";
    }
    gCtx.imager->show();
    return;
}
