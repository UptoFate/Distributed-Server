#include "MysqlMgr.h"


MysqlMgr::~MysqlMgr() {

}

int MysqlMgr::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
    return _dao.get()->RegUser(name, email, pwd);
}

MysqlMgr::MysqlMgr() {
    CREATE_PROPERTIES(prop, conf);

    const auto& host = prop.getProperty("Mysql.Host");
    const auto& port = prop.getProperty("Mysql.Port");
    const auto& pwd = prop.getProperty("Mysql.Passwd");
    const auto& schema = prop.getProperty("Mysql.Schema");
    const auto& user = prop.getProperty("Mysql.User");

    _dao = std::make_unique<MysqlDao>(host, port, pwd, schema, user);
}

bool MysqlMgr::CheckPwd(const std::string& name, const std::string& pwd, UserInfo& userInfo) {
    return _dao.get()->CheckPwd(name, pwd, userInfo);
}

std::shared_ptr<UserInfo> MysqlMgr::GetUser(int uid)
{
    return _dao.get()->GetUser(uid);
}
