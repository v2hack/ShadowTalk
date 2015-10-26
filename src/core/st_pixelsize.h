#ifndef POINTSIZETOPIXELSIZE_H
#define POINTSIZETOPIXELSIZE_H

#include <QObject>
#include <QQuickItem>
#include <QGuiApplication>

class PointSizeToPixelSize : public QObject
{
    Q_OBJECT
public:
    PointSizeToPixelSize(QObject *parent = 0);
    ~PointSizeToPixelSize();

    /* 像素点支持尺寸大小计算 */
    Q_INVOKABLE int pixelSize(int pointSize);

    /* 计算界面文字高度 */
    Q_INVOKABLE int height(int pointSize);

    /* 计算界面文字高度 */
    Q_INVOKABLE int width(int pointSize, QString text);

signals:

public slots:
};

#endif // POINTSIZETOPIXELSIZE_H
