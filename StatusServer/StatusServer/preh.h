﻿#pragma once
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <memory>
#include <iostream>
#include "Singleton.h"
#include <functional>
#include <map>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "util/Properties.h"
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cassert>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,  //Json解析错误
    RPCFailed = 1002,  //RPC请求错误
    VarifyExpired =1003,//验证码过期
    VarifyCodeErr =1004,//验证码错误
    UserExist = 1005,//用户已存在
    PassErr = 1006, //密码错误
    EmailNotMatch = 1007, //邮箱不匹配
    PasswdUpFailed = 1008, //密码更新失败
    PasswdInvalid = 1009, //密码更新失败
    RPCGetFailed = 1010,
    UidInvalid = 1011,
    TokenInvalid = 1012
};

class Defer {
public:
    //接受一个lambda表达式或函数指针
    Defer(std::function<void()> func ): func_(func){}

    ~Defer() {
        func_();
    }

private:
    std::function<void()> func_;
};

#define CODEPREFIX "code_"

#define USERIPPREFIX  "uip_"
#define USERTOKENPREFIX  "utoken_"
#define IPCOUNTPREFIX  "ipcount_"
#define USER_BASE_INFO "ubaseinfo_"
#define LOGIN_COUNT  "logincount"
#define NAME_INFO  "nameinfo_"

struct UserInfo
{
    std::string name;
    std::string pwd;
    int uid;
    std::string email;
};