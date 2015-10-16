#ifndef ST_TRAY_ICON_H_
#define ST_TRAY_ICON_H_

#include <QSystemTrayIcon>
#include <QWindow>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    TrayIcon(QWindow *win, QObject *parent = 0);
    ~TrayIcon();

    void setWindow(QWindow *window) {
        m_window = window;
    }

    const QIcon & icon() {
        return m_icon;
    }
    void onRemind(const QString &contents);


protected slots:
    void onTrayIconActivated( QSystemTrayIcon::ActivationReason reason);
    void onExit();

protected:
    QSystemTrayIcon * m_trayIcon;
    QMenu * m_trayMenu;
    QWindow * m_window;
    QIcon m_icon;
};



#endif //ST_TRAY_ICON_H_
