#include "httpmgr.h"
#include <Qfile.h>
HttpMgr::HttpMgr()
{
    // 加载 CA 证书
    QFile certFile(":/certs/server.crt");  // 使用资源文件或本地文件路径
    if (certFile.open(QIODevice::ReadOnly)) {
        QSslCertificate cert(&certFile, QSsl::Pem);
        QList<QSslCertificate> certs = QSslConfiguration::defaultConfiguration().caCertificates();
        certs.append(cert);
        QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
        sslConfig.setCaCertificates(certs);
        QSslConfiguration::setDefaultConfiguration(sslConfig);
    }
    else {
        qDebug() << "Failed to load CA certificate!";
    }
    //连接http请求和完成信号，信号槽机制保证队列消费
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

HttpMgr::~HttpMgr()
{

}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId req_id, Modules mod)
{
    //创建一个HTTP POST请求，并设置请求头和请求体
    QByteArray data = QJsonDocument(json).toJson();
    //通过url构造请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    
    if (url.scheme() == "https") {
        QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
        request.setSslConfiguration(sslConfig);

        // 如果需要忽略 SSL 错误（如证书不匹配，测试环境），可以使用以下代码
        QObject::connect(&_manager, &QNetworkAccessManager::sslErrors,
            [](QNetworkReply* reply, const QList<QSslError>& errors) {
                qDebug() << "忽略 SSL 错误:";
                // 遍历并打印每个 SSL 错误
                for (const QSslError& error : errors) {
                    qDebug() << "SSL Error:" << error.errorString();
                }
                reply->ignoreSslErrors();  // 忽略所有 SSL 错误（仅在测试时使用）
            });

    }
    
    
    //发送请求，并处理响应, 获取自己的智能指针，构造伪闭包并增加智能指针引用计数
    auto self = shared_from_this();
    QNetworkReply* reply = _manager.post(request, data);
    //设置信号和槽等待发送完成
    QObject::connect(reply, &QNetworkReply::finished, [reply, self, req_id, mod]() {
        //处理错误的情况
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(req_id, "", ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        //无错误则读回请求
        QString res = reply->readAll();

        //发送信号通知完成
        emit self->sig_http_finish(req_id, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
        });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod)
{
    if (mod == Modules::REGISTERMOD) {
        //发送信号通知指定模块http响应结束
        emit sig_reg_mod_finish(id, res, err);
    }

    if (mod == Modules::LOGINMOD) {
        emit sig_login_mod_finish(id, res, err);
    }
}