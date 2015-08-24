
#include <fstream>
#include <string>

#include <QMap>
#include <QDebug>
#include <QString>
#include <QGuiApplication>

#include "st_voice.h"
#include "st_utils.h"
#include "st_cache.h"
#include "st_context.h"
#include "st_message.h"


extern struct ShadowTalkContext gCtx;

Voice::Voice(QObject *parent) : QObject(parent) {
}

void Voice::writeVoiceFile(std::string fileName, std::string data) {
//    std::ofstream outfile (fileName, std::ofstream::binary);
//    outfile.write(data.c_str(), data.size());
//    outfile.close();

    std::ofstream file;
    file.open(fileName, std::ios::out | std::ios::binary);
    file.write(data.c_str(), data.size());
    file.close();
}


std::string Voice::findVoiceCache(QString fidx, QString midx) {

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
        if (m.messageType == MessageTypeVoice) {
            return m.data;
        }
    }
	return std::string("");
}

void Voice::playVoice(QString fidx, QString midx) {

    qDebug() << "play voice :  - " << fidx << " : " << midx;
    QString filePath = QString("%0%1-%2%3").arg(SHADOWTALK_TEMP_DIR, fidx,
                    midx, SHADOWTALK_SOUND_PREFIX);

    std::string friendVoice = findVoiceCache(fidx, midx);
    if (friendVoice.empty()) {
        qDebug() << "voice is empty";
        return;
    }
    writeVoiceFile(filePath.toStdString(), friendVoice);


    QString tempPath = QString("%0%1%2-%3%4").arg(
                QGuiApplication::applicationDirPath(),"/temp/", fidx, midx, SHADOWTALK_SOUND_PREFIX);


    const QUrl commandLineUrl = QUrl::fromLocalFile(tempPath);
    qDebug() << "voice file :  - " << commandLineUrl;
    gCtx.viewer->rootContext()->setContextProperty(QStringLiteral("voiceUrl"), commandLineUrl);

    playMessageVoice(tempPath);

}

void Voice::stopVoice() {

}
