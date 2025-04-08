#include "loginDialog.h"
#include "httpmgr.h"
#include "tcpMgr.h"
#include "customWidgets.h"

LoginDialog::~LoginDialog()
{}

LoginDialog::LoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

    //测试ui
    //textInputItem* username = new textInputItem("用户名:", this);
    //username->setValue("");
    //username->setFixedWidth(330);
    //username->move(30, 0);
    //textInputItem* passwd = new textInputItem("密 码:", this);
    //passwd->setValue("");
    //passwd->setFixedWidth(330);
    //passwd->move(30, 30);


	connect(ui.reg_btn, &QPushButton::clicked, this, &LoginDialog::switchRegister);
	ui.forget_label->SetState("normal", "hover", "", "selected", "selected_hover", "");
	connect(ui.forget_label, &ClickedLabel::clicked, this, &LoginDialog::slot_forget_pwd);
	ui.pass_edit->setEchoMode(QLineEdit::Password);

	connect(ui.login_btn, &QPushButton::clicked, [this]() {

/***************************************/
        /*#ifdef DEBUG 无须登录*/
        emit TcpMgr::GetInstance()->sig_switch_maindlg();
        return;
/***************************************/

        qDebug() << "login btn clicked";

        enableBtn(false);
        auto user = ui.user_edit->text();
        auto pwd = ui.pass_edit->text();
        //发送http请求登录
        QJsonObject json_obj;
        json_obj["user"] = user;
        json_obj["passwd"] = xorString(pwd);
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/user_login"),
            json_obj, ReqId::ID_LOGIN_USER, Modules::LOGINMOD);
		});

    //头像什么的
    //initHead();

    initHttpHandlers();

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this, &LoginDialog::slot_login_mod_finish);
    //连接tcp连接请求的信号和槽函数
    connect(this, &LoginDialog::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
    //连接tcp管理者发出的连接成功信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &LoginDialog::slot_tcp_con_finish);

    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_login_failed, this, &LoginDialog::slot_login_failed);
}

bool LoginDialog::enableBtn(bool enabled)
{
    ui.login_btn->setEnabled(enabled);
    ui.reg_btn->setEnabled(enabled);
    return true;
}

void LoginDialog::showTip(QString str, bool b_ok)
{
    if (!b_ok) {
        ui.err_tip->setProperty("state", "err");
    }
    else {
        ui.err_tip->setProperty("state", "normal");
    }

    ui.err_tip->setText(str);

    repolish(ui.err_tip);
}


void LoginDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips, false);
}

void LoginDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if (_tip_errs.empty()) {
        ui.err_tip->clear();
        return;
    }

    showTip(_tip_errs.first(), false);
}

void LoginDialog::slot_forget_pwd()
{
	emit switchReset();
}

void LoginDialog::initHttpHandlers()
{
    //注册获取登录回包逻辑
    _handlers.insert(ReqId::ID_LOGIN_USER, [this](QJsonObject jsonObj) {
        int error = jsonObj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }

        auto user = jsonObj["user"].toString();
        ServerInfo si;
        si.uid = jsonObj["uid"].toInt();
        si.Host = jsonObj["host"].toString();
        si.Port = jsonObj["port"].toString();
        si.Token = jsonObj["token"].toString();

        _uid = si.uid;
        _token = si.Token;
        
        showTip(tr("登录成功"), true);
        qDebug() << "user is " << user << ", uid is " << si.uid << " host is " << si.Host << " port is " << si.Port << " token is " << si.Token;
        
        emit sig_connect_tcp(si);
        });

}

void LoginDialog::slot_login_mod_finish(ReqId id, QString res, ErrorCodes err)
{
    enableBtn(true);
    if (err != ErrorCodes::SUCCESS) {
        showTip(tr("网络请求错误"), false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if (jsonDoc.isNull()) {
        showTip(tr("json解析错误"), false);
        return;
    }

    //json解析错误
    if (!jsonDoc.isObject()) {
        showTip(tr("json解析错误"), false);
        return;
    }


    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());

    return;
}

void LoginDialog::slot_tcp_con_finish(bool bsuccess)
{

    if (bsuccess) {
        showTip(tr("登录成功，正在连接服务器..."), true);
        QJsonObject jsonObj;
        jsonObj["uid"] = _uid;
        jsonObj["token"] = _token;

        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);

        //发送tcp请求给chat server
        TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN, jsonString);

    }
    else {
        showTip(tr("网络异常"), false);
        enableBtn(true);
    }

}

void LoginDialog::slot_login_failed(int err)
{
    QString result = QString("登录失败, err is %1").arg(err);

    showTip(result, false);
    enableBtn(true);
}