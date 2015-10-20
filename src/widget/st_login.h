#ifndef ST_LOGIN_H_
#define ST_LOGIN_H_


class Login
{
public:
    static void ShadowTalkSetSyncProcess(int processValue);
    static int  ShadowTalkLogin();
    static void ShadowTalkLoginStartSync();
    static void ShadowTalkLoginClean();
    static void ShadowTalkSetSyncProcessClean(int processValue);
};

#endif //ST_LOGIN_H_

