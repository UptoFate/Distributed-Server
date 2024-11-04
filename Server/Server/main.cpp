#include"GateServer.h"
#include "RedisMgr.h"

int main()
{
    CREATE_PROPERTIES(prop, conf);
    string Gate_port_str = prop.getProperty("GateServer.Port");
    string Varify_port_str = prop.getProperty("VarifyServer.Port");
    unsigned short gate_port = atoi(Gate_port_str.c_str());
    unsigned short verify_port = atoi(Varify_port_str.c_str());

    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_options(
        boost::asio::ssl::context::default_workarounds |
        boost::asio::ssl::context::no_sslv2 |
        boost::asio::ssl::context::single_dh_use);

    // 设置服务器的证书和私钥
    ssl_context.use_certificate_chain_file("certs/server.crt");
    ssl_context.use_private_key_file("certs/private.key", boost::asio::ssl::context::pem);


    try
    {
        net::io_context ioc{ 1 };
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {

            if (error) {
                return;
            }
            ioc.stop();
            });
        //std::make_shared<GateServer>(ioc, gate_port)->Start();
        std::make_shared<GateServer>(ioc, gate_port, ssl_context)->Start();
        ioc.run();
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

//启动服务器，在浏览器输入`http://localhost:8082/get_test`
//
//会看到服务器回包`receive get_test req`
//
//如果我们输入带参数的url请求`http://localhost:8082/get_test?key1=value1&key2=value2`
//
//会收到服务器反馈`url not found`
//
//所以对于get请求带参数的情况我们要实现参数解析，我们可以自己实现简单的url解析函数

