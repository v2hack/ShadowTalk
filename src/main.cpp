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


QGuiApplication *globalApp;


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    globalApp = &app;

    /* 设置程序路径 */
    QString dir = QGuiApplication::applicationDirPath();
    QDir::setCurrent(dir);

    /* 库加载路径 */
    QGuiApplication::addLibraryPath("./plugins");

    /* 注册C++类型到QML */
    qmlRegisterType<PointSizeToPixelSize>("st.font.PointSizeToPixelSize", 1, 0, "PointSizeToPixelSize");

    /* 加载qml */
    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    /* 注册C++类型到QML为属性 */
//    viewer.rootContext()->setContextProperty("PointSizeToPixelSize", new PointSizeToPixelSize);

    /* 设置无边框及透明 */
    viewer.setFlags(Qt::FramelessWindowHint|Qt::Window);
    viewer.setColor(QColor(Qt::transparent));

    /* viewer注册到qml */
    QQmlContext *qml_context = viewer.rootContext();
    if (qml_context) {
        qml_context->setContextProperty("mainwindow", &viewer);
    }
    viewer.show();
    return app.exec();
}
