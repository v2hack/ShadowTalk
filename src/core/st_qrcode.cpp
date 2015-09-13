#include "st_qrcode.h"

#include <QPainter>
#include <QImage>

QrCode::QrCode() {
    qr = NULL;
}

QrCode::~QrCode() {
    if(qr != NULL) {
        QRcode_free(qr);
    }
}

/**
 *  功能描述: 获取Qr的长度
 *  @param pointSize  文字像素点
 *
 *  @return 无
 */
int QrCode::getQRWidth() const {
    if(qr != NULL) {
        return qr->width;
    } else {
        return 0;
    }
}

/**
 *  功能描述: 设置生成Qrcode的字符串
 *  @param str 这里是Qrchannel的id
 *
 *  @return 无
 */
void QrCode::setString(QString str) {
    string = str;
    if(qr != NULL) {
        QRcode_free(qr);
    }
    qr = QRcode_encodeString(string.toStdString().c_str(),
                             1, QR_ECLEVEL_L, QR_MODE_8, 1);
    return;
}

/**
 *  功能描述: 设置Qrcode图片的大小
 *  @param 无
 *
 *  @return 无
 */
QSize QrCode::sizeHint() const {
    QSize s;
    if(qr != NULL){
        int qr_width = qr->width > 0 ? qr->width : 1;
        s = QSize(qr_width * 4, qr_width * 4);
    } else {
        s = QSize(50, 50);
    }
    return s;
}

/**
 *  功能描述: 设置Qrcode图片最小尺寸
 *  @param 无
 *
 *  @return 无
 */
QSize QrCode::minimumSizeHint() const {
    QSize s;
    if(qr != NULL) {
        int qr_width = qr->width > 0 ? qr->width : 1;
        s = QSize(qr_width, qr_width);
    } else {
        s = QSize(50, 50);
    }
    return s;
}

/**
 *  功能描述: 将Qrcode保存为图片
 *  @param  fileName 文件名
 *  @param  size 文件像素大小
 *
 *  @return 成功true  失败false
 */
bool QrCode::saveImage(QString fileName, int size) {
    if(size != 0 && !fileName.isEmpty()) {
        QImage image(size, size, QImage::Format_Mono);
        QPainter painter(&image);
        QColor background(Qt::white);
        painter.setBrush(background);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0, 0, size, size);
        if(qr != NULL) {
            draw(painter, size, size);
        }
        return image.save(fileName);
    } else {
        return false;
    }
}

/**
 *  功能描述: 根据计算出来的长和宽，画图
 *  @param  painter Qt画笔
 *  @param  width  图片宽
 *  @param  height 图片高
 *
 *  @return 成功true  失败false
 */
void QrCode::draw(QPainter &painter, int width, int height) {
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    const int qr_width = qr->width > 0 ? qr->width : 1;
    double scale_x = width / qr_width;
    double scale_y = height / qr_width;
    for (int y = 0; y < qr_width; y ++) {
        for (int x = 0; x < qr_width; x++) {
            unsigned char b = qr->data[y * qr_width + x];
            if (b & 0x01) {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
}
