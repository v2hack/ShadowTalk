#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QGuiApplication>

#include <QtQuick/QQuickView>
#include <QtQml>

#include "pixelsize.h"
#include "friend.h"
#include "cache.h"

/* app全局索引 */
QGuiApplication *globalApp = NULL;
QQuickView *globalViewer = NULL;
Cache *globalCache = NULL;


/* 设置启动参数 */
void setAppParameter() {

    /* 设置程序路径 */
    QString dir = QGuiApplication::applicationDirPath();
    QDir::setCurrent(dir);

    /* 库加载路径 */
    QGuiApplication::addLibraryPath("./plugins");
    return;
}


/* 注册QML类型 */
void registerQmlTye() {
    /* 注册C++类型到QML */
    qmlRegisterType<PointSizeToPixelSize>("st.font.PointSizeToPixelSize",
                1, 0, "PointSizeToPixelSize");
//    qmlRegisterType<ShadowTalkCache>("st.widget.ShadowTalkCache",
//                1, 0, "ShadowTalkCache");
    return;
}


/* 注册QML属性 */
void registerQMlProperty(QQuickView &viewer) {
    /* 注册C++类型到QML为属性 */
    viewer.rootContext()->setContextProperty("ShadowTalkCache", globalCache);
    return;
}


void setViewerParameter(QQuickView &viewer) {
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    /* 设置无边框及透明 */
    viewer.setFlags(Qt::FramelessWindowHint|Qt::Window);
    viewer.setColor(QColor(Qt::transparent));

    /* viewer注册到qml */
    QQmlContext *qmlContext = viewer.rootContext();
    if (qmlContext) {
        qmlContext->setContextProperty("mainwindow", &viewer);
    }
}


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    globalApp = &app;

    /* 设置启动参数 */
    setAppParameter();

    /* 注册QML */
    registerQmlTye();

    /* 设置viwer参数 */
    QQuickView viewer;
    globalViewer = &viewer;
    setViewerParameter(viewer);

        viewer.show();

    /* 缓存初始化 */
    globalCache = new Cache;
    if (!globalCache) {
        qDebug() << "c++: " << "malloc for globalCache fail";
        exit(0);
    }


    return app.exec();
}
