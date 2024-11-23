//#pragma once
//
//#include <string>
//#include <vector>
//#include <fstream>
//#include <sstream>
//#include <cstring>
//#include <stdexcept>
//#include <openssl/aes.h>
//#include <openssl/evp.h>
//#include <openssl/sha.h>
//#include <openssl/rand.h>
//#include "Device.h"
//#include "singleton.h"
//#include "global.h"
//#include "UserMgr.h"
//
//#ifdef _WIN32
//#pragma comment(lib, "Crypt32.lib")
//#include <windows.h>
//#include <wincrypt.h>
//#include <dpapi.h>
//#elif defined(__APPLE__)
//#include <Security/Security.h>
//#else
//#include <libsecret/secret.h>
//#endif
//
//
//class AuthMgr :public Singleton<AuthMgr>,
//    public std::enable_shared_from_this<AuthMgr>
//{
//public:
//    friend class Singleton<AuthMgr>;
//    ~AuthMgr();
//
//    // 令牌数据结构
//    struct Token {
//        std::string accessToken;
//        std::string refreshToken;
//        std::string offlineToken;
//        long long expiryTime;
//    };
//
//private:
//
//    const std::string TOKEN_FILE_PATH = "token_path.dat";
//    const int KEY_SIZE = 32; // AES-256
//    const int IV_SIZE = 16;
//
//
//    AuthMgr();
//
//    // 根据机器指纹生成加密密钥
//    std::vector<unsigned char> generateEncryptionKey();
//
//    // AES 加密
//    std::vector<unsigned char> encryptAES(const std::string& data, const std::vector<unsigned char>& key);
//
//    // AES 解密
//    std::string decryptAES(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& key);
//
//    // 系统安全存储
//    void systemProtect(const std::vector<unsigned char>& data, const std::string& filename);
//
//public:
//    // 保存令牌
//    void saveToken();
//
//    // 读取令牌
//    Token loadToken();
//
//    // 验证令牌有效性
//    bool validateToken(const Token& token);
//};
//
