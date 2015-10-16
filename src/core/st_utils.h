#ifndef UTILS_H
#define UTILS_H

#include <Qstring>
#include <QObject>
#include <QThread>

#include "st_context.h"
#include "st_cache.h"
#include "st_friend.h"
#include "st_group.h"

#define ST_SUCCESS 0
#define ST_CREATE_QRCODE_FAIL -1

#define SHADOWTALK_TEMP_DIR       "./temp/"  /* 临时文件目录 */
#define SHADOWTALK_IMAGE_PREFIX   ".jpg"     /* 图片文件扩展名 */
#define SHADOWTALK_SOUND_PREFIX   ".mp3"     /* 声音文件扩展名 */

void ShadowTalkSleep(unsigned int msec);

void playMessageSound();
void playMessageVoice(QString voiceFilePath);
void stopMessageVoice();

void displayCurrentFriendName(QString currentFriendName);
void displayLoginView();
void displayBaseView();

void setMainWindowVisible();
void setMainWindowUnvisible();

void addFriendIntoWidget(QString friendName, int friendIndex, int listViewIndex);
void addGroupIntoWidget(QString groupName, int groupIndex, int listViewIndex);
void walkCacheAddFriendAndGroup();

void clearCurrentItemHighLight(Cache *cache);
void setGroupItemHighLight(Cache *cache,  Group *group, int groupCacheindex);
void setFriendItemHighLight(Cache *cache,  Friend *friend_, int friendCacheIndex);


class WindowClose : public QObject {
    Q_OBJECT

public:
    WindowClose(QObject *parent = 0);
    ~WindowClose();
    Q_INVOKABLE void closeWindowProcess();
};


#endif // UTILS_H


