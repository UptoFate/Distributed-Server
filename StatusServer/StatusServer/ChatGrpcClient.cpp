#include "ChatGrpcClient.h"

ChatGrpcClient::ChatGrpcClient()
{
    CREATE_PROPERTIES(prop, conf);

    //auto server_list = cfg["PeerServer"]["Servers"];
    auto server_list = prop.getProperty("chatservers");
    std::vector<std::string> words;

    std::stringstream ss(server_list);
    std::string word;

    while (std::getline(ss, word, ',')) {
        words.push_back(word);
    }

    for (auto& word : words) {
        if (prop.getProperty(word)=="") {
            continue;
        }
        _pools[prop.getProperty(word)] = std::make_unique<ChatConPool>(5, prop.getProperty(word+".Host"), prop.getProperty(word + ".Port"));
    }

}

//AddFriendRsp ChatGrpcClient::NotifyAddFriend(std::string server_ip, const AddFriendReq& req) {
//    AddFriendRsp rsp;
//    return rsp;
//}
//
//AuthFriendRsp ChatGrpcClient::NotifyAuthFriend(std::string server_ip, const AuthFriendReq& req) {
//    AuthFriendRsp rsp;
//    return rsp;
//}

bool ChatGrpcClient::GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo) {
    return true;
}

//TextChatMsgRsp ChatGrpcClient::NotifyTextChatMsg(std::string server_ip,
//    const TextChatMsgReq& req, const Json::Value& rtvalue) {
//
//    TextChatMsgRsp rsp;
//    return rsp;
//}