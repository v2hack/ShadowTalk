/*******************************************************************
 *  Copyright(c) 2014-2015 PeeSafe
 *  All rights reserved.
 *
 *  文件名称:
 *  简要描述:
 *
 *  当前版本:1.0
 *  作者: 南野
 *  日期: 2015/07/20
 *  说明:
 ******************************************************************/
#include "st_trayicon.h"
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QApplication>
#include <QMenu>

/**
 *  功能描述: 系统托盘构建函数
 *  @param 无
 *
 *  @return 无
 */
TrayIcon::TrayIcon(QWindow *win, QObject *parent) : QObject(parent), m_window(win)
    , m_icon(":/img/st_icon.png")
{
    m_trayIcon = new QSystemTrayIcon(this);
    connect(m_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(onTrayIconActivated(QSystemTrayIcon::ActivationReason)));
    m_trayIcon->setIcon(m_icon);
    m_trayIcon->setToolTip(tr("stock monitor"));

    /* 将托盘菜单的父设置为桌面，托盘菜单在失去焦点时会自动消失 */
    m_trayMenu = new QMenu((QWidget*)QApplication::desktop());
    m_trayMenu->addAction(tr("Exit"), this, SLOT(onExit()));
    m_trayIcon->setContextMenu(m_trayMenu);
    m_trayIcon->show();
}

/**
 *  功能描述: 析构函数
 *  @param 无
 *
 *  @return 无
 */
TrayIcon::~TrayIcon() {
}

/**
 *  功能描述: 系统托盘激活
 *  @param 无
 *
 *  @return 无
 */
void TrayIcon::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick && m_window) {
        switch(m_window->windowState()) {
        case Qt::WindowMinimized:
            m_window->showNormal();
            break;
        }
        m_window->requestActivate();
    }
}

/**
 *  功能描述: 系统托盘拖出
 *  @param 无
 *
 *  @return 无
 */
void TrayIcon::onExit()
{
    m_trayIcon->hide();
    QApplication::exit(0);
}

/**
 *  功能描述: 系统托盘消息提醒
 *  @param 无
 *
 *  @return 无
 */
void TrayIcon::onRemind(const QString &contents)
{
    m_trayIcon->showMessage(tr("Notification"), contents);
}
