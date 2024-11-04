#pragma once
#include"preh.h"
#include"Singleton.h"
#include"util/Properties.h"
#include"message.grpc.pb.h"
#include"message.pb.h"
#include"data.h"
#include<grpcpp/grpcpp.h>

using grpc::Channel;

using message::GetChatServerReq;
using message::ChatService;


//用于与peerserver通信的gRPC服务器
class ChatServiceImpl final : public ChatService::Service
{
public:
    ChatServiceImpl();
    //Status NotifyAddFriend(ServerContext* context, const AddFriendReq* request,
    //    AddFriendRsp* reply) override;

    //Status NotifyAuthFriend(ServerContext* context,
    //    const AuthFriendReq* request, AuthFriendRsp* response) override;

    //Status NotifyTextChatMsg(::grpc::ServerContext* context,
    //    const TextChatMsgReq* request, TextChatMsgRsp* response) override;

    bool GetBaseInfo(std::string base_key, int uid, std::shared_ptr<UserInfo>& userinfo);

private:
};