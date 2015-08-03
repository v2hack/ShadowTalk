/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称:
 *  简要描述:
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include <Qstring>
#include "login.h"
#include "utils.h"


/* 生成二维码 */
QString ShadowTalkCreateQrCode(QString qrCodeSource) {



}

/* 将二维码图片设置到页面上 */
void ShadowTalkQrImage(QString qrImagePath) {

}


/* 添加好友控件 */
void ShadowTalkAddFriendWidget() {


    // 添加控件


    // 好友添加到cache


}




/* 登陆 */
int ShadowTalkLogin() {
    QString qrCodeSource;

    /* 利用peersafe接口创建二维码 */
    //qrCodeSource = XXX

    /* 创建二维码图片 */
    QString qrImagePath = ShadowTalkCreateQrCode(qrCodeSource);
    if (qrImagePath.isEmpty()) {
        return ST_CREATE_QRCODE_FAIL;
    }

    /* 界面上设置二维码图片*/
    ShadowTalkQrImage(qrImagePath);


    return ST_SUCCESS;
}


