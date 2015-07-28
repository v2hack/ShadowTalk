#include "pixelsize.h"
#include <QString>
#include <QDebug>
#include <QScreen>
#include <QFont>
#include <QFontMetricsF>


PointSizeToPixelSize::PointSizeToPixelSize(QObject *parent) {
    return;
}

PointSizeToPixelSize::~PointSizeToPixelSize() {
    return;
}


int PointSizeToPixelSize::pixelSize(int pointSize) {
    QScreen *screen = globalApp->primaryScreen();
    if (!screen) {
        return 0;
    }
    int point_size = (pointSize * screen->logicalDotsPerInch()) / 75;
    return point_size;
}

int PointSizeToPixelSize::height(int pointSize) {
    QFont font = globalApp->font();
    font.setPointSize(pointSize);
    QFontMetrics fm(font);
//    qDebug() << "c++: height - " << fm.height();
    return fm.height();
}

int PointSizeToPixelSize::width(int pointSize, QString text) {
    QFont font = globalApp->font();
    font.setPointSize(pointSize);
    QFontMetrics fm(font);
//    qDebug() << "c++: width - " << fm.width(text);
    return fm.width(text);
}
