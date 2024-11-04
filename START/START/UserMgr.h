#pragma once

#include <QObject>
#include <memory>
#include "singleton.h"

class UserMgr :public QObject, public Singleton<UserMgr>,
    public std::enable_shared_from_this<UserMgr>
{
    Q_OBJECT
public:
    friend class Singleton<UserMgr>;
    ~UserMgr();
    void SetName(QString name);
    void SetUid(int uid);
    void SetToken(QString token);
private:
    UserMgr();
    QString _name;
    QString _token;
    QString _cpuID;
    QString _biosID;
    int _uid;
};
