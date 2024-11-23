#pragma once

#include <QDialog>
#include "ui_loginDialog.h"
#include "global.h"

class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	LoginDialog(QWidget *parent = nullptr);
	~LoginDialog();
	void showTip(QString str, bool b_ok);
private:
	Ui::LoginDialogClass ui;
	QMap<TipErr, QString> _tip_errs;
	QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
	void AddTipErr(TipErr te, QString tips);
	void DelTipErr(TipErr te);
	void initHttpHandlers();	//回调函数
	bool enableBtn(bool enabled);
	int _uid;
	QString _token;
signals:
	void switchRegister();
	void switchReset();
	void sig_connect_tcp(ServerInfo);

private slots:
	void slot_forget_pwd();
	void slot_login_mod_finish(ReqId id, QString res, ErrorCodes err);
	void slot_tcp_con_finish(bool bsuccess);
	void slot_login_failed(int err);
};
