//#include "AuthMgr.h"
//
//AuthMgr::~AuthMgr()
//{
//}
//
//AuthMgr::AuthMgr()
//{
//    OpenSSL_add_all_algorithms();
//}
//
//std::vector<unsigned char> AuthMgr::generateEncryptionKey()
//{
//    std::stringstream ss;
//    ss << UserMgr::GetInstance()->getCpuID().toStdString() << UserMgr::GetInstance()->getBiosID().toStdString();
//
//    unsigned char hash[SHA256_DIGEST_LENGTH];
//    SHA256_CTX sha256;
//    SHA256_Init(&sha256);
//    SHA256_Update(&sha256, ss.str().c_str(), ss.str().length());
//    SHA256_Final(hash, &sha256);
//
//    return std::vector<unsigned char>(hash, hash + KEY_SIZE);
//}
//
//// AES 鍔犲瘑瀹炵幇
//std::vector<unsigned char> AuthMgr::encryptAES(const std::string& data, const std::vector<unsigned char>& key)
//{
//    // 鐢熸垚闅忔満IV
//    std::vector<unsigned char> iv(IV_SIZE);
//    if (RAND_bytes(iv.data(), IV_SIZE) != 1) {
//        throw std::runtime_error("Failed to generate random IV");
//    }
//
//    // 鍒濆鍖栧姞瀵嗕笂涓嬫枃
//    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
//    if (!ctx) {
//        throw std::runtime_error("Failed to create cipher context");
//    }
//
//    // 鍒濆鍖栧姞瀵嗘搷浣?
//    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key.data(), iv.data()) != 1) {
//        EVP_CIPHER_CTX_free(ctx);
//        throw std::runtime_error("Failed to initialize encryption");
//    }
//
//    // 棰勫垎閰嶈緭鍑虹紦鍐插尯
//    std::vector<unsigned char> ciphertext(iv.size() + data.size() + EVP_MAX_BLOCK_LENGTH);
//    std::copy(iv.begin(), iv.end(), ciphertext.begin());
//
//    int len;
//    // 鍔犲瘑鏁版嵁
//    if (EVP_EncryptUpdate(ctx, ciphertext.data() + IV_SIZE, &len,
//        (const unsigned char*)data.c_str(), data.length()) != 1) {
//        EVP_CIPHER_CTX_free(ctx);
//        throw std::runtime_error("Failed to encrypt data");
//    }
//    int ciphertext_len = len;
//
//    // 瀹屾垚鍔犲瘑
//    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + IV_SIZE + len, &len) != 1) {
//        EVP_CIPHER_CTX_free(ctx);
//        throw std::runtime_error("Failed to finalize encryption");
//    }
//    ciphertext_len += len;
//
//    // 鑾峰彇璁よ瘉鏍囩
//    unsigned char tag[16];
//    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag) != 1) {
//        EVP_CIPHER_CTX_free(ctx);
//        throw std::runtime_error("Failed to get authentication tag");
//    }
//
//    // 娣诲姞璁よ瘉鏍囩鍒板瘑鏂?
//    ciphertext.insert(ciphertext.end(), tag, tag + 16);
//    ciphertext_len += 16;
//
//    EVP_CIPHER_CTX_free(ctx);
//
//    // 璋冩暣vector澶у皬涓哄疄闄呭瘑鏂囬暱搴?
//    ciphertext.resize(IV_SIZE + ciphertext_len);
//    return ciphertext;
//}
//
//std::string AuthMgr::decryptAES(const std::vector<unsigned char>& ciphertext, const std::vector<unsigned char>& key) 
//{
//    if (ciphertext.size() <= IV_SIZE) {
//        throw std::runtime_error("Invalid ciphertext");
//    }
//
//    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
//    std::vector<unsigned char> iv(ciphertext.begin(),
//        ciphertext.begin() + IV_SIZE);
//
//    std::vector<unsigned char> plaintext(ciphertext.size() - IV_SIZE);
//    int len;
//
//    EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key.data(), iv.data());
//    EVP_DecryptUpdate(ctx, plaintext.data(), &len,
//        ciphertext.data() + IV_SIZE,
//        ciphertext.size() - IV_SIZE);
//
//    int plaintext_len = len;
//    EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len);
//    plaintext_len += len;
//
//    EVP_CIPHER_CTX_free(ctx);
//    return std::string(plaintext.begin(),
//        plaintext.begin() + plaintext_len);
//}
//
//void AuthMgr::systemProtect(const std::vector<unsigned char>& data, const std::string& filename) 
//{
//
//#ifdef _WIN32
//    // Windows DPAPI
//    DATA_BLOB dataIn, dataOut;
//    dataIn.pbData = (BYTE*)data.data();
//    dataIn.cbData = data.size();
//
//    if (!CryptProtectData(&dataIn, nullptr, nullptr, nullptr, nullptr, 0, &dataOut)) {
//        throw std::runtime_error("Failed to protect data with DPAPI");
//    }
//
//    std::ofstream file(filename, std::ios::binary);
//    file.write((char*)dataOut.pbData, dataOut.cbData);
//    LocalFree(dataOut.pbData);
//
//#elif defined(__APPLE__)
//    // MacOS Keychain
//    SecKeychainAddGenericPassword(nullptr,
//        strlen("JetBrains IDE"),
//        "JetBrains IDE",
//        strlen("auth_token"),
//        "auth_token",
//        data.size(),
//        data.data(),
//        nullptr);
//
//#else
//    // Linux libsecret
//    SecretSchema schema = {
//        "org.jetbrains.ide.token",
//        SECRET_SCHEMA_NONE,
//        {
//            { "application", SECRET_SCHEMA_ATTRIBUTE_STRING },
//            { "type", SECRET_SCHEMA_ATTRIBUTE_STRING },
//            { nullptr, SECRET_SCHEMA_ATTRIBUTE_STRING }
//        }
//    };
//
//    secret_password_store_sync(&schema,
//        SECRET_COLLECTION_DEFAULT,
//        "JetBrains IDE Token",
//        (char*)data.data(),
//        nullptr,
//        nullptr,
//        "application", "JetBrains IDE",
//        "type", "auth_token",
//        nullptr);
//#endif
//
//}
//
//void AuthMgr::saveToken() 
//{
//
//    // 1. 鐢熸垚鍔犲瘑瀵嗛挜
//    std::vector<unsigned char> key = generateEncryptionKey();
//
//    // 2. 鍔犲瘑鏁版嵁
//    std::vector<unsigned char> encrypted = encryptAES(UserMgr::GetInstance()->getToken().toStdString(), key);
//
//    // 3. 浣跨敤绯荤粺API淇濇姢骞跺瓨鍌?
//    systemProtect(encrypted, TOKEN_FILE_PATH);
//}
//
//// 鍔犺浇浠ょ墝瀹炵幇
//AuthMgr::Token AuthMgr::loadToken()
//{
//    std::vector<unsigned char> encrypted;
//    Token token;
//
//#ifdef _WIN32
//    // Windows DPAPI瑙ｅ瘑
//    std::ifstream file(TOKEN_FILE_PATH, std::ios::binary);
//    if (!file) {
//        throw std::runtime_error("Failed to open token file");
//    }
//
//    // 璇诲彇鍔犲瘑鏁版嵁
//    file.seekg(0, std::ios::end);
//    size_t size = file.tellg();
//    file.seekg(0, std::ios::beg);
//    std::vector<unsigned char> encrypted_data(size);
//    file.read((char*)encrypted_data.data(), size);
//
//    // 浣跨敤DPAPI瑙ｅ瘑
//    DATA_BLOB dataIn, dataOut;
//    dataIn.pbData = encrypted_data.data();
//    dataIn.cbData = encrypted_data.size();
//    if (!CryptUnprotectData(&dataIn, nullptr, nullptr, nullptr, nullptr, 0, &dataOut)) {
//        throw std::runtime_error("Failed to unprotect data with DPAPI");
//    }
//    encrypted = std::vector<unsigned char>(dataOut.pbData, dataOut.pbData + dataOut.cbData);
//    LocalFree(dataOut.pbData);
//
//#else
//    // Linux libsecret璇诲彇
//    SecretSchema schema = {
//        "org.ide.token",
//        SECRET_SCHEMA_NONE,
//        {
//            { "application", SECRET_SCHEMA_ATTRIBUTE_STRING },
//            { "type", SECRET_SCHEMA_ATTRIBUTE_STRING },
//            { nullptr, SECRET_SCHEMA_ATTRIBUTE_STRING }
//        }
//    };
//
//    char* secret = secret_password_lookup_sync(&schema,
//        nullptr, nullptr,
//        "application", "JetBrains IDE",
//        "type", "auth_token",
//        nullptr);
//
//    if (!secret) {
//        throw std::runtime_error("Failed to read from secret service");
//    }
//
//    encrypted = std::vector<unsigned char>((unsigned char*)secret,
//        (unsigned char*)secret + strlen(secret));
//    secret_password_free(secret);
//#endif
//
//    // 浣跨敤鏈哄櫒鎸囩汗鐢熸垚鐨勫瘑閽ヨВ瀵嗘暟鎹?
//    std::vector<unsigned char> key = generateEncryptionKey();
//    std::string decrypted = decryptAES(encrypted, key);
//
//    // 瑙ｆ瀽JSON鏍煎紡鐨勪护鐗屾暟鎹?
//    try {
//        // 鍋囪浣跨敤绠€鍗曠殑鍒嗛殧绗︽牸寮忓瓨鍌ㄤ护鐗屾暟鎹?
//        std::stringstream ss(decrypted);
//        std::getline(ss, token.accessToken, '|');
//        std::getline(ss, token.refreshToken, '|');
//        std::getline(ss, token.offlineToken, '|');
//        ss >> token.expiryTime;
//    }
//    catch (const std::exception& e) {
//        throw std::runtime_error("Failed to parse token data: " + std::string(e.what()));
//    }
//
//    return token;
//}
//
//bool AuthMgr::validateToken(const Token& token)
//{
//    // 妫€鏌ヤ护鐗屾槸鍚︿负绌?
//    if (token.accessToken.empty() || token.refreshToken.empty()) {
//        return false;
//    }
//
//    // 妫€鏌ユ槸鍚﹁繃鏈?
//    long long currentTime = std::time(nullptr);
//    if (currentTime >= token.expiryTime) {
//        return false;
//    }
//
//    // 鍙互娣诲姞鍏朵粬楠岃瘉閫昏緫锛屾瘮濡?
//    // 1. 楠岃瘉浠ょ墝鏍煎紡
//    // 2. 妫€鏌ヤ护鐗岀鍚?
//    // 3. 楠岃瘉绂荤嚎浠ょ墝
//    // 4. 涓庢湇鍔″櫒閫氫俊楠岃瘉浠ょ墝鐘舵€?
//
//    return true;
//}