#include "usermgr.h"
#include "Device.h"
UserMgr::~UserMgr()
{
    _cpuID = QString::fromStdString( secure::device::GetDeviceID::GetCpuID());
    _biosID = QString::fromStdString(secure::device::GetDeviceID::GetBiosID());
}

void UserMgr::SetName(QString name)
{
    _name = name;
}

void UserMgr::SetUid(int uid)
{
    _uid = uid;
}

void UserMgr::SetToken(QString token)
{
    _token = token;
}

QString UserMgr::getName()
{
    return _name;
}

QString UserMgr::getCpuID()
{
    return _cpuID;
}

QString UserMgr::getBiosID()
{
    return _biosID;
}

int UserMgr::getUid()
{
    return _uid;
}

QString UserMgr::getToken()
{
    return _token;
}

UserMgr::UserMgr()
{

}