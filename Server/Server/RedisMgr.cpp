#include "RedisMgr.h"
RedisMgr::~RedisMgr()
{
}

RedisMgr::RedisMgr() {
        // Redis 连接选项
        CREATE_PROPERTIES(prop, conf);
        string host = prop.getProperty("Redis.Host");
        string port_str = prop.getProperty("Redis.Port");
        string password = prop.getProperty("Redis.Passwd");
        string db_str = prop.getProperty("Redis.db");
        sw::redis::ConnectionOptions connection_options;
        connection_options.host = host;  // Redis 服务器的地址
        connection_options.port = atoi(port_str.c_str());         // Redis 服务器的端口
        connection_options.password = password; // 如果有密码，设置密码
        connection_options.db = atoi(db_str.c_str());              // 使用的数据库，默认是 0

        // Redis 连接池选项
        sw::redis::ConnectionPoolOptions pool_options;
        pool_options.size = 10;  // 设置连接池的大小
        pool_options.wait_timeout = std::chrono::milliseconds(100); // 等待可用连接的超时时间
        pool_options.connection_lifetime = std::chrono::minutes(10); // 每个连接的生命周期

        // 创建一个 Redis 对象，连接池配置通过选项传递
        redis_ = std::make_unique<sw::redis::Redis>(connection_options, pool_options);
        std::cout << "Redis 连接池初始化成功！" << std::endl;
}


bool RedisMgr::Get(const std::string& key, std::string& value)
{
    // 使用 Redis 连接池获取键值
    auto val = redis_.get()->get(key);

    // 检查是否成功获取到值
    if (!val) {
        std::cout << "[ GET " << key << " ] failed" << std::endl;
        return false;
    }
    else {
        // 将获取到的值赋给引用参数
        value = *val;
        std::cout << "Succeed to execute command [ GET " << key << " ]: " << value << std::endl;
        return true;
    }
}

bool RedisMgr::Set(const std::string& key, const std::string& value) 
{
    return redis_.get()->set(key, value);;
}

bool RedisMgr::LPush(const std::string& key, const std::string& value)
{
    return redis_.get()->lpush(key, value);
}

bool RedisMgr::LPop(const std::string& key, std::string& value) {
    // 使用 Redis 连接池获取键值
    auto val = redis_.get()->lpop(key);

    // 检查是否成功获取到值
    if (!val) {
        return false;
    }
    else {
        // 将获取到的值赋给引用参数
        value = *val;
        return true;
    }
}

bool RedisMgr::RPush(const std::string& key, const std::string& value) {
    
    return redis_.get()->rpush(key, value);;
}

bool RedisMgr::RPop(const std::string& key, std::string& value) {
    auto val = redis_.get()->rpop(key);
    value = *val;
    return true;
}

bool RedisMgr::HSet(const std::string& key, const std::string& hkey, const std::string& value) {
    
    return redis_.get()->hset(key, hkey, value);;
}


bool RedisMgr::HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen)
{
    std::string value(hvalue, hvaluelen);

    // 使用 Redis 连接对象执行 HSET 命令
    auto result = redis_.get()->hset(key, hkey, value);

    // 如果 result 返回 false，表示字段已存在或操作失败
    if (!result) {
        std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] failure !" << std::endl;
        return false;
    }

    std::cout << "Execut command [ HSet " << key << "  " << hkey << "  " << value << " ] success !" << std::endl;
    return true;
}

std::string RedisMgr::HGet(const std::string& key, const std::string& hkey)
{
    return *redis_.get()->hget(key, hkey);
}

bool RedisMgr::Del(const std::string& key)
{
    return redis_.get()->del(key);
}

bool RedisMgr::ExistsKey(const std::string& key)
{
    return   redis_.get()->exists(key);
}