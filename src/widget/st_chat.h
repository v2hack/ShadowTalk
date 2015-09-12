#ifndef CHATLIST_H
#define CHATLIST_H

#include <QObject>

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);

signals:

public slots:
};

#endif // CHATLIST_H
