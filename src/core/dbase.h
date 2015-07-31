#ifndef DBASE_H
#define DBASE_H

#include <QObject>

class ShadowTalkSqlite : public QObject
{
    Q_OBJECT
public:
    explicit ShadowTalkSqlite(QObject *parent = 0);
    ~ShadowTalkSqlite();

    bool sqliteCheckExist();
    void sqliteCreateDbase();


signals:

public slots:
};

#endif // DBASE_H
