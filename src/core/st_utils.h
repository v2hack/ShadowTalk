#ifndef UTILS_H
#define UTILS_H

#include <Qstring>
#include <QObject>
#include <QThread>

#include "st_context.h"
#include "st_cache.h"
#include "st_friend.h"
#include "st_group.h"

#define SHADOWTALK_TEMP_DIR       "./temp/"  /* 临时文件目录 */
#define SHADOWTALK_IMAGE_PREFIX   ".jpg"     /* 图片文件扩展名 */
#define SHADOWTALK_SOUND_PREFIX   ".mp3"     /* 声音文件扩展名 */

class Utils
{
public:
    static void ShadowTalkSleep(unsigned int msec);

    static void playMessageSound();
    static void playMessageVoice(QString voiceFilePath);
    static void stopMessageVoice();

    static void displayCurrentFriendName(QString currentFriendName);
    static void displayLoginView();

    static void addFriendIntoWidget(QString friendName, int friendIndex, int listViewIndex);
    static void addGroupIntoWidget(QString groupName, int groupIndex, int listViewIndex);
    static void walkCacheAddFriendAndGroup();

    static void clearCurrentItemHighLight(Cache *cache);
    static void setGroupItemHighLight(Cache *cache,  Group *group, int groupCacheindex);
    static void setFriendItemHighLight(Cache *cache,  Friend *friend_, int friendCacheIndex);
};



class WindowClose : public QObject
{
    Q_OBJECT
public:
    WindowClose(QObject *parent = 0);
    ~WindowClose();
    Q_INVOKABLE void closeWindowProcess();
};


#endif // UTILS_H


