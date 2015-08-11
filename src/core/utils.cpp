#include <QTime>
#include <QObject>
#include <QGuiApplication>

/**
 *  功能描述: 休眠函数
 *  @param msec 毫秒
 *
 *  @return 无
 */
void ShadowTalkSleep(unsigned int msec) {
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
