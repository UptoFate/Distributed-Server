#pragma once
#include"preh.h"
#include <boost/asio/ssl.hpp>

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
    friend class LogicSystem;
public:
    HttpConnection(boost::asio::io_context& ioc, boost::asio::ssl::context& ssl_context);
    //HttpConnection(boost::asio::io_context & ioc);
    void Start();
    //tcp::socket& GetSocket();
    boost::asio::ssl::stream<tcp::socket>& GetSocket();
private:
    void ReadRequest();

    void CheckDeadline();
    void WriteResponse();
    void HandleReq();
    std::string _get_url;
    std::unordered_map<std::string, std::string> _get_params;
    //tcp::socket  _socket;
    boost::asio::ssl::stream<tcp::socket> _socket;
    //用于配置SSL证书等信息
    boost::asio::ssl::context& _ssl_context;

    // The buffer for performing reads.
    beast::flat_buffer  _buffer{ 8192 };

    // The request message.
    http::request<http::dynamic_body> _request;

    // The response message.
    http::response<http::dynamic_body> _response;

    // The timer for putting a deadline on connection processing.
    net::steady_timer deadline_{
        _socket.get_executor(), std::chrono::seconds(60) 
    };

    void PreParseGetParam();
};

