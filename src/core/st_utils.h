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

    /* 播放接收消息声音 */
    static void playMessageSound();

    /* 访问qml对象，播放音频文件 */
    static void playMessageVoice(QString voiceFilePath);

    /* 功能描述: 访问qml对象，停止播放语音 */
    static void stopMessageVoice();

    /* 设置界面上当前好友的名字 */
    static void displayCurrentFriendName(QString currentFriendName);

    /* 界面切换，设置登录页面隐藏*/
    static void displayLoginView();

    /* 将缓存中的好友添加到界面 */
    static void addFriendIntoWidget(QString friendName, int friendIndex, int listViewIndex);

    /* 将缓存中的组添加到界面 */
    static void addGroupIntoWidget(QString groupName, int groupIndex, int listViewIndex);

    /* 联系人页面，按照首字符显示好友 */
    static void walkCacheAddFriendAndGroup();

    /* 清除当前用户选中的高亮 */
    static void clearCurrentItemHighLight(Cache *cache);

    /* 设置组item高亮 */
    static void setGroupItemHighLight(Cache *cache,  Group *group, int groupCacheindex);

    /* 设置好友item高亮 */
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


