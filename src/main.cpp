#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    viewer.setFlags(Qt::FramelessWindowHint|Qt::Window);
    viewer.setColor(QColor(Qt::transparent));

    QQmlContext *qml_context = viewer.rootContext();
    if (qml_context) {
        qml_context->setContextProperty("mainwindow", &viewer);
    }
    viewer.show();
    return app.exec();

}
