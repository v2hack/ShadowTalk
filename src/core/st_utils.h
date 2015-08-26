#ifndef UTILS_H
#define UTILS_H

#include <Qstring>
#include <QObject>

#define ST_SUCCESS 0
#define ST_CREATE_QRCODE_FAIL -1

#ifdef LINUX
#define SHADOWTALK_TEMP_DIR  "./temp/"  /* 临时文件目录 */
#else
#define SHADOWTALK_TEMP_DIR  "./temp/"  /* 临时文件目录 */
#endif

#define SHADOWTALK_IMAGE_PREFIX   ".jpg"  /* 图片文件扩展名 */
#define SHADOWTALK_SOUND_PREFIX   ".mp3"  /* 声音文件扩展名 */

void ShadowTalkSleep(unsigned int msec);
void playMessageSound();
void playMessageVoice(QString voiceFilePath);
void displayCurrentFriendName(QString currentFriendName);




#endif // UTILS_H


