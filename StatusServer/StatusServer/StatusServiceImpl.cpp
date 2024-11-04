#include "StatusServiceImpl.h"
#include "preh.h"
#include "RedisMgr.h"

std::string generate_unique_string() {
    // 创建UUID对象
    boost::uuids::uuid uuid = boost::uuids::random_generator()();

    // 将UUID转换为字符串
    std::string unique_string = to_string(uuid);

    return unique_string;
}

Status StatusServiceImpl::GetChatServer(ServerContext* context, const GetChatServerReq* request, GetChatServerRsp* reply)
{
    std::string prefix("status server has received :  ");
    _server_index = (++_server_index) % (_servers.size());
    auto& server = _servers[_server_index];
    reply->set_host(server.host);
    reply->set_port(server.port);
    reply->set_error(ErrorCodes::Success);
    auto token_value = generate_unique_string();
    reply->set_token(token_value);

    std::string uid_str = std::to_string(request->uid());
    std::string token_key = USERTOKENPREFIX + uid_str;
    bool success = RedisMgr::GetInstance()->Set(token_key, token_value);
    return Status::OK;
}


Status StatusServiceImpl::Login(ServerContext* context, const LoginReq* request, LoginRsp* reply)
{
    auto uid = request->uid();
    auto token = request->token();

    std::string uid_str = std::to_string(uid);
    std::string token_key = USERIPPREFIX + uid_str;
    std::string token_value = "";
    bool success = RedisMgr::GetInstance()->Get(token_key, token_value);
    if (!success) {
        reply->set_error(ErrorCodes::UidInvalid);
        return Status::OK;
    }
    if (token!=token_value) {
        reply->set_error(ErrorCodes::TokenInvalid);
        return Status::OK;
    }
    reply->set_error(ErrorCodes::Success);
    reply->set_uid(uid);
    reply->set_token(token);
    return Status::OK;
}

StatusServiceImpl::StatusServiceImpl() :_server_index(0)
{
    CREATE_PROPERTIES(prop, conf);
    ChatServer server;
    server.port = prop.getProperty("ChatServer1.Port");
    server.host = prop.getProperty("ChatServer1.Host");
    _servers.push_back(server);

    server.port = prop.getProperty("ChatServer2.Port");
    server.host = prop.getProperty("ChatServer2.Host");
    _servers.push_back(server);
}