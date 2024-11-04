#pragma once
#include <sw/redis++/redis++.h>
#include "preh.h"


class RedisMgr : public Singleton<RedisMgr>,
    public std::enable_shared_from_this<RedisMgr>
{
    friend class Singleton<RedisMgr>;
public:
    ~RedisMgr();
    bool Get(const std::string& key, std::string& value);
    bool Set(const std::string& key, const std::string& value);
    bool LPush(const std::string& key, const std::string& value);
    bool LPop(const std::string& key, std::string& value);
    bool RPush(const std::string& key, const std::string& value);
    bool RPop(const std::string& key, std::string& value);
    bool HSet(const std::string& key, const std::string& hkey, const std::string& value);
    bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);
    std::string HGet(const std::string& key, const std::string& hkey);
    bool Del(const std::string& key);
    bool ExistsKey(const std::string& key);

private:
    RedisMgr();
    std::unique_ptr<sw::redis::Redis> redis_;
};


//// 设置连接池参数
//sw::redis::Redis create_redis_connection_pool(size_t size = 300) {
//    // Redis 连接选项
//    CREATE_PROPERTIES(prop, conf);
//    string host = prop.getProperty("Redis.Host");
//    string port_str = prop.getProperty("Redis.Port");
//    string password = prop.getProperty("Redis.Passwd");
//    string db_str = prop.getProperty("Redis.db");
//    sw::redis::ConnectionOptions connection_options;
//    connection_options.host = host;  // Redis 服务器的地址
//    connection_options.port = atoi(port_str.c_str());         // Redis 服务器的端口
//    connection_options.password = password; // 如果有密码，设置密码
//    connection_options.db = atoi(db_str.c_str());              // 使用的数据库，默认是 0
//
//    // Redis 连接池选项
//    sw::redis::ConnectionPoolOptions pool_options;
//    pool_options.size = size;  // 设置连接池的大小
//    pool_options.wait_timeout = std::chrono::milliseconds(100); // 等待可用连接的超时时间
//    pool_options.connection_lifetime = std::chrono::minutes(10); // 每个连接的生命周期
//
//    // 创建一个 Redis 对象，连接池配置通过选项传递
//    return sw::redis::Redis(connection_options, pool_options);
//};

//void TestRedis() {
//    try {
//        // 创建Redis实例，连接到Redis服务器
//        auto redis = sw::redis::Redis("tcp://192.168.88.129:6380");
//
//        // 进行身份验证
//        std::string redis_password = "123456";
//        redis.auth(redis_password);
//        std::cout << "Redis认证成功！" << std::endl;
//
//        // 设置key值
//        redis.set("stest1", "value1");
//        std::cout << "设置键'stest1'成功" << std::endl;
//
//        // 获取字符串长度
//        auto length = redis.strlen("stest1");
//        std::cout << "The length of 'stest1' is " << length << "." << std::endl;
//
//        // 获取键的值
//        auto val = redis.get("stest1");
//        if (val) {  // 检查是否存在
//            std::cout << "The value of 'stest1' is " << *val << std::endl;
//        }
//        else {
//            std::cout << "'stest1' does not exist." << std::endl;
//        }
//
//        // 尝试获取一个不存在的键
//        auto val2 = redis.get("stest2");
//        if (val2) {
//            std::cout << "The value of 'stest2' is " << *val2 << std::endl;
//        }
//        else {
//            std::cout << "'stest2' does not exist." << std::endl;
//        }
//
//    }
//    catch (const sw::redis::Error& err) {
//        std::cerr << "Redis操作失败: " << err.what() << std::endl;
//    }
//}

//void test_multithreads(int thread_num, int times) {
//    sw::redis::Redis redis = create_redis_connection_pool(thread_num);
//    std::vector<std::string> keys;
//    keys.reserve(thread_num);
//    for (auto idx = 0; idx != thread_num; ++idx) {
//        auto key = "multi-threads::" + std::to_string(idx);
//        keys.push_back(key);
//        redis.set(key, key);
//    }
//
//    std::vector<std::thread> workers;
//    workers.reserve(thread_num);
//    for (const auto& key : keys) {
//        workers.emplace_back([&redis, key, times]() {
//            try {
//                for (auto i = 0; i != times; ++i) {
//                    auto val = redis.get(key);
//                    if (!val) {
//                        std::cout << "failed to test multithreads, cannot get value of " + key << std::endl;
//                        return;
//                    }
//                }
//            }
//            catch (std::exception& e) {
//                std::cerr << "failed to test multithreads, " << e.what() << std::endl;
//                return;
//            }
//            });
//    }
//
//    for (auto& worker : workers) {
//        worker.join();
//    }
//}