#ifndef QRCODE_H
#define QRCODE_H

#include <QString>
#include <QSize>
#include <QPainter>
#include <QPaintEvent>

#include "qrencode.h"

class QrCode
{
public:
    explicit QrCode();
    ~QrCode();

    void setString(QString str);
    int getQRWidth() const;
    bool saveImage(QString name, int size);

private:
    void draw(QPainter &painter, int width, int height);
    QString string;
    QRcode *qr;


signals:

protected:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
public slots:
};

#endif // QRCODE_H
