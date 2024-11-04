#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <windows.h>
#include <iphlpapi.h>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <memory>
#include <QTcpSocket>
#include <QJsonObject> // { }
#include <QJsonArray> // [ ]
#include <QJsonDocument> // 解析Json
#include <QJsonValue> // int float double bool null { } [ ]
#include <QJsonParseError>
#include <qsslsocket.h>

#include "ui_Login.h"
#include "Device.h"


using namespace std;

class Login : public QMainWindow
{
    Q_OBJECT
public:
    Login(QWidget* parent = nullptr);
    ~Login();
    void sendMessage();

private:
    Ui::LoginClass ui;
    //database *_database;
    //void Free(); 
    QTcpSocket* socket;
    //QSslSocket* socket;
private slots:
    void pushButton1_Clicked();
    void readMessage();
};
