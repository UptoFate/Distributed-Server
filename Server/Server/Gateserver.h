#pragma once
#include "preh.h"
#include "HttpConnection.h"
class GateServer :public std::enable_shared_from_this<GateServer>
{
public:
    GateServer(boost::asio::io_context& ioc, unsigned short& port, boost::asio::ssl::context& ssl_context);
    void Start();
private:
    tcp::acceptor  _acceptor;
    net::io_context& _ioc;
    boost::asio::ssl::context& _ssl_context; // 添加 SSL 上下文
};


