#ifndef UTILS_H
#define UTILS_H

#include <Qstring>
#include <QObject>
#include <QThread>

#define ST_SUCCESS 0
#define ST_CREATE_QRCODE_FAIL -1

#define SHADOWTALK_TEMP_DIR       "./temp/"  /* 临时文件目录 */
#define SHADOWTALK_IMAGE_PREFIX   ".jpg"     /* 图片文件扩展名 */
#define SHADOWTALK_SOUND_PREFIX   ".mp3"     /* 声音文件扩展名 */

void ShadowTalkSleep(unsigned int msec);

void playMessageSound();
void playMessageVoice(QString voiceFilePath);
void stopMessageVoice();

void writeXmlFile(std::string fileName, std::string data);
int  parseEncryptXml(QString fileName, QString passwd);

void displayCurrentFriendName(QString currentFriendName);
void displayLoginView();
void displayBaseView();

void setMainWindowVisible();
void setMainWindowUnvisible();

void addFriendIntoWidget(QString friendName, int friendIndex);
void walkCacheAddFriend();

#endif // UTILS_H


