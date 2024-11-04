#include "GateServer.h"
#include "AsioIOServicePool.h"

//GateServer::GateServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc),
//_acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {
//
//}

GateServer::GateServer(boost::asio::io_context& ioc, unsigned short& port, boost::asio::ssl::context& ssl_context)
    : _ioc(ioc),
    _acceptor(ioc, tcp::endpoint(tcp::v4(), port)),
    _ssl_context(ssl_context) { // 初始化 SSL 上下文
}

void GateServer::Start()
{
    auto self = shared_from_this();
    auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
    
    // 创建支持 SSL 的 HttpConnection 实例
    std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context, _ssl_context);

    _acceptor.async_accept(new_con->GetSocket().lowest_layer(), [self, new_con](beast::error_code ec) {
        try {
            //出错则放弃这个连接，继续监听新链接
            if (ec) {
                self->Start();
                return;
            }

            //处理新链接，创建HpptConnection类管理新连接
            new_con->Start();
            //继续监听
            self->Start();
        }
        catch (std::exception& exp) {
            std::cout << "exception is " << exp.what() << std::endl;
            self->Start();
        }
        });
}