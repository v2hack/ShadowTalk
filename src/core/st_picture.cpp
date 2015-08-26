
#include <fstream>
#include <string>

#include <QMap>
#include <QDebug>
#include <QString>
#include <QGuiApplication>
#include <QString>

#include "st_utils.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_message.h"
#include "st_picture.h"

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
    return std::string("");
}


QString displayPicture(QString fidx, QString midx, std::string pictureData) {

    /* 组装文件路径及名字 */
    QString tempFilePath = QString("%0%1-%2%3").arg(
        SHADOWTALK_TEMP_DIR,
        fidx,
        midx,
        SHADOWTALK_IMAGE_PREFIX);

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
    return pictureUrl.toString();
}
