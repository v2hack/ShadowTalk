#include "friend.h"
#include <QWidget>
#include <QtQuick/QQuickView>
#include <QThread>

extern QQuickView *globalViewer;


void sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

Friend::Friend()
{
    QQuickItem *rootObject = globalViewer->rootObject();
    if (rootObject == NULL) {
        return;
    }

    QVariantMap newElement1;
    QVariantMap newElement2;
    QVariantMap newElement3;
    newElement1.insert("name", "Image1");
    newElement2.insert("name", "Image2");
    newElement3.insert("name", "Image3");

    QObject *rect = rootObject->findChild<QObject*>("FriendListMod");
    if (rect) {
        sleep(10);
        QMetaObject::invokeMethod(rect, "addFriend", Q_ARG(QVariant, QVariant::fromValue(newElement1)));
        sleep(10);
        QMetaObject::invokeMethod(rect, "addFriend", Q_ARG(QVariant, QVariant::fromValue(newElement2)));
        sleep(10);
        QMetaObject::invokeMethod(rect, "addFriend", Q_ARG(QVariant, QVariant::fromValue(newElement3)));
        qDebug() << "find it";
    } else {
        qDebug() << "can not find";
    }
}


Friend::~Friend()
{



}
