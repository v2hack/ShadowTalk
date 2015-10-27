#ifndef VOICE_H
#define VOICE_H

#include <QObject>
#include <QString>
#include <string>

class Voice : public QObject
{
    Q_OBJECT
public:
    explicit Voice(QObject *parent = 0);

    /* 将声音缓存写入文件 */
    void writeVoiceFile(std::string fileName, std::string data);

    /* 根据qml索引，查找相应的缓存 */
    std::string findVoiceCache(QString fidx, QString midx);

    /* 播放语音操作 */
    Q_INVOKABLE void playVoice(QString friendIndex, QString messageIndex);

    /* 停止播放语音 */
    Q_INVOKABLE void stopVoice();
};

#endif // VOICE_H
