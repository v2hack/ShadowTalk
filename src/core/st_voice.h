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

    void writeVoiceFile(std::string fileName, std::string data);
    std::string findVoiceCache(QString fidx, QString midx);
    Q_INVOKABLE void playVoice(QString friendIndex, QString messageIndex);
    Q_INVOKABLE void stopVoice();


signals:

public slots:
};

#endif // VOICE_H
