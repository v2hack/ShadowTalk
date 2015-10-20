/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称: st_voice.cpp
 *  简要描述: 主要负责语音的显示、播放
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
#include <fstream>
#include <string>
#include "st_voice.h"
#include "st_utils.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_message.h"

/* 全局上下文结构 */
extern struct ShadowTalkContext gCtx;

/**
 *  功能描述: Voice 声音的构造函数
 *  @param  无
 *
 *  @return 无
 */
Voice::Voice(QObject *parent) : QObject(parent) {}

/**
 *  功能描述: 将声音缓存写入文件
 *  @param fileName 文件名
 *  @param data 音频文件数据
 *
 *  @return 无
 */
void Voice::writeVoiceFile(std::string fileName, std::string data)
{
    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::binary);
    file.write(data.c_str(), data.size());
    file.close();
    return;
}

/**
 *  功能描述: 根据qml索引，查找相应的缓存
 *  @param fidx 好友id
 *  @param midx 消息id
 *
 *  @return 无
 */
std::string Voice::findVoiceCache(QString fidx, QString midx)
{
    Cache *c = gCtx.cache;
    if (!c) {
        return std::string("");
    }

    /* 找到好友缓存 */
    Friend *f = c->getOneFriend(fidx.toInt());
    if (!f) {
        qDebug() << "[c++] : can't find friend index - " << fidx;
        return std::string("");
    }

    /* 如果是音频消息则返回内容 */
    QMap<int, Message>::iterator it = f->messageList.find(midx.toInt());
    if (it != f->messageList.end()) {
        Message &m = it.value();
        if (m.messageType == MessageTypeVoice) {
            return m.data;
        }
    }
    return std::string("");
}

/**
 *  功能描述: 播放语音操作
 *  @param fidx 好友id
 *  @param midx 消息id
 *
 *  @return 无
 */
void Voice::playVoice(QString fidx, QString midx)
{
    /* 找到缓存并生成声音文件 */
    std::string friendVoice = findVoiceCache(fidx, midx);
    if (friendVoice.empty()) {
        qDebug() << "[c++] : voice is empty : fidx - " << fidx << " midx - " << midx;
        return;
    }

	/* 组装文件路径及名字 */
    QString tempFilePath = QString("%0%1-%2%3").arg(SHADOWTALK_TEMP_DIR,
        fidx, midx, SHADOWTALK_SOUND_PREFIX);

	std::string friendVoiceFile = tempFilePath.toStdString();
    writeVoiceFile(friendVoiceFile, friendVoice);

    /* 拼装文件绝对路径，并设置qml播放的source属性 */
    QString tempPath = QString("%0%1%2-%3%4").arg(QGuiApplication::applicationDirPath(),
                "/temp/", fidx, midx, SHADOWTALK_SOUND_PREFIX);

    const QUrl commandLineUrl = QUrl::fromLocalFile(tempPath);
    gCtx.viewer->rootContext()->setContextProperty(QStringLiteral("voiceUrl"), commandLineUrl);
    qDebug() << "[c++] : voice file :  - " << commandLineUrl;

    /* 调用qml播放声音接口 */
    Utils::playMessageVoice(tempPath);
    return;
}

/**
 *  功能描述: 休眠函数
 *  @param msec 毫秒
 *
 *  @return 无
 */
void Voice::stopVoice()
{
    Utils::stopMessageVoice();
    return;
}
