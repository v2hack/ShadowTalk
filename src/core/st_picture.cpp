
#include <fstream>
#include <string>

#include <QMap>
#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QString>
#include <QQuickView>

#include "st_utils.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_message.h"
#include "st_picture.h"
#include "st_context.h"
#include "st_cache.h"

/* 全局上下文结构 */
extern struct ShadowTalkContext gCtx;


void writePictureFile(std::string fileName, std::string data) {
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::binary);
    file.write(data.c_str(), data.size());
    file.close();
    return;
}

std::string findPictureCache(QString fidx, QString midx) {

    /* 寻找index的消息 */
    Cache *c = gCtx.cache;
    if (!c) {
        qDebug() << "gctx cache is empty";
        return std::string("");
    }

    /* 找到好友缓存 */
    Friend *f = c->getOneFriend(fidx.toInt());
    if (!f) {
        qDebug() << "can't find friend index - " << fidx;
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

    qDebug() << "can't find image message";
    return std::string("");
}


QUrl displayPicture(QString fidx, QString midx, std::string pictureData) {

    /* 组装文件路径及名字 */
    QString tempFilePath = QString("%0%1-%2%3").arg(
        SHADOWTALK_TEMP_DIR, fidx, midx, SHADOWTALK_IMAGE_PREFIX);
    std::string friendPictureFile = tempFilePath.toStdString();
    writePictureFile(friendPictureFile, pictureData);

    /* 拼装文件绝对路径，并设置qml播放的source属性 */
    QString tempPath = QString("%0%1%2-%3%4").arg(
                QGuiApplication::applicationDirPath(),
                "/temp/",
                fidx,
                midx,
                SHADOWTALK_IMAGE_PREFIX);
    const QUrl pictureUrl = QUrl::fromLocalFile(tempPath);
    return pictureUrl;
}

int shrinkPicture(QString filePath, int &height, int &width, int limit) {

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


NormalPicture::NormalPicture(QObject *parent) : QObject(parent) {

}

static void setViewerParameter(QQuickView &viewer, QString qmlProperty, QString qmlFile) {
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

void NormalPicture::displayNormalPicture(QString friendIndex, QString messageIndex) {
    qDebug() << "display large picture";

    if (gCtx.imager == NULL) {
        gCtx.imager = new QQuickView;
    }
    setViewerParameter(*gCtx.imager, "pictureWindow", "qrc:/qml/picture.qml");


    qDebug() << "normal picture fidx - " << friendIndex << "midx - " << messageIndex;
    std::string fileData = findPictureCache(friendIndex, messageIndex);
    if (fileData.empty()) {
        qDebug() << "normal picture is empty";
        return;
    }
    /* 持久化图片文件 */
    QUrl picturePath = displayPicture(friendIndex, messageIndex, fileData);
    if (picturePath.isEmpty()) {
        return;
    }

    int height = 0, width = 0;
    if (shrinkPicture(picturePath.toLocalFile(), height, width, 600) < 0) {
        qDebug() << "shrink picture fail";
        return;
    }
    qDebug() << "normal picture height - " << height << "width - " << width;

    /* 添加qml对象属性 */
    QQuickItem *rootObject = gCtx.imager->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QObject *rect = rootObject->findChild<QObject*>("qmlNormalImage");
    if (rect) {
        QMetaObject::invokeMethod(rect, "setPicture",
                                  Q_ARG(QVariant, picturePath.toString()),
                                  Q_ARG(QVariant, height),
                                  Q_ARG(QVariant, width)
                                  );
        qDebug() << "insert one picture ok";
    } else {
        qDebug() << "insert one picture fail";
    }
    gCtx.imager->show();
}



