#ifndef UTILS_H
#define UTILS_H

#include <Qstring>

#define ST_SUCCESS 0
#define ST_CREATE_QRCODE_FAIL -1


void ShadowTalkSleep(unsigned int msec);
void playMessageSound();
void displayCurrentFriendName(QString currentFriendName);

#endif // UTILS_H


