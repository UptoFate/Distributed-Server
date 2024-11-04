#pragma once

#include <QDialog>
#include "ui_registerdialog.h"
#include "global.h"


class Httpmgr;

class RegisterDialog : public QDialog
{
	Q_OBJECT

public:
	RegisterDialog(QWidget *parent = nullptr);
	~RegisterDialog();

	void showTip(QString str, bool b_ok);
private:

	QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
	QMap<TipErr, QString> _tip_errs;
	QTimer* _countdown_timer;
	int _countdown;

	void AddTipErr(TipErr te, QString tips);
	void DelTipErr(TipErr te);
	void ChangeTipPage();
	bool checkUserValid();
	bool checkPassValid();
	bool checkConfirmValid();
	bool checkEmailValid();
	bool checkVarifyValid();

	Ui::RegisterDialogClass ui;
	void initHttpHandlers();
private slots:
	void on_get_code_clicked();
	void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
	void on_confirm_btn_clicked();

signals:
	void sigSwitchLogin();
};
