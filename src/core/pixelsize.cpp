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
    return fm.height();
}

int PointSizeToPixelSize::width(int pointSize, QString text) {
    QFont font = globalApp->font();
    font.setPointSize(pointSize);
    QFontMetrics fm(font);
    return fm.width(text);
}
