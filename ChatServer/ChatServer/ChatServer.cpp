#include "LogicSystem.h"
#include <csignal>
#include <thread>
#include <mutex>
#include "AsioIOServicePool.h"
#include "CServer.h"
#include "util/Properties.h"
#include "RedisMgr.h"
#include "ChatGrpcClient.h"

bool bstop = false;
std::condition_variable cond_quit;
std::mutex mutex_quit;

int main()
{
    CREATE_PROPERTIES(prop, conf);

    try {
        auto pool = AsioIOServicePool::GetInstance();

        //将登录数设置为0
        RedisMgr::GetInstance()->HSet(LOGIN_COUNT, "ChatServer1", "0");

        //定义一个GrpcServer
        //std::string server_address(cfg["SelfServer"]["Host"] + ":" + cfg["SelfServer"]["RPCPort"]);
        //ChatServiceImpl service;
        //grpc::ServerBuilder builder;
        // 构建并启动gRPC服务器
        //std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
        //std::cout << "RPC Server listening on " << server_address << std::endl;
        ////单独启动一个线程处理grpc服务
        //std::thread  grpc_server_thread([&server]() {
        //    server->Wait();
        //    });


        boost::asio::io_context  io_context;

        boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&io_context, pool](auto, auto) {
            io_context.stop();
            pool->Stop();
            });


        auto port_str = prop.getProperty("SelfServer.Port");
        CServer s(io_context, atoi(port_str.c_str()));
        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << endl;
    }

}