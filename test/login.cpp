#include "stdafx.h"
#include "login.h"

Login::Login(QWidget *parent) 
    : QMainWindow(parent), /*_database(new database()), */socket(new QTcpSocket(this))//socket(new QSslSocket(this))
{
    ui.setupUi(this);

}

Login::~Login()
{
    /*delete _database;*/
}

void Login::pushButton1_Clicked()
{
    //if (_database->ValidateLogon(ui.userNameEdit->text(), ui.passWordEdit->text()) == false) {
    //    QMessageBox::information(this, "Login", "ValidateLogon is false.");
    //}
    //else {
    //    QMessageBox::information(this, "Login", "SUCCESS");
    //    _database->sqlUpdate(ui.userNameEdit->text());
    //}

    QString ip = ui.lineEditIP->text();
    qint16 port = ui.lineEditPort->text().toInt();
    //QString ip = "192.168.88.129";
    //qint16 port = 5050;


    connect(socket, SIGNAL(readyRead()), this, SLOT(readMessage()));
    socket->connectToHost(ip.trimmed(), port);
    //int fd = socket->socketDescriptor();
    //SSL* ssl = init_ssl("./cert.pem", "./key.pem", SSL_MODE_CLIENT, fd);

    QString str = "{\"CMD\": \"LOGIN\", \"username\": \"";
    str.append(ui.userNameEdit->text());
    str.append("\", \"password\": \"");
    str.append(ui.passWordEdit->text());
    str.append("\", \"CpuID\": \"");
    str.append(QString::fromStdString(secure::device::GetDeviceID::GetCpuID()));
    str.append("\", \"BiosID\": \"");
    str.append(QString::fromStdString(secure::device::GetDeviceID::GetBiosID()));
    str.append("\"}");
    socket->write(str.toUtf8());

}

void Login::sendMessage()
{
    //{"CMD": "LOGIN", "username": "lm", "password": "123456"}
}

void Login::readMessage()
{
    QByteArray arr = socket->readAll();
    QString str = arr.data();
    ui.textEditRead->setText(str);


    QJsonParseError jsonError;
    // ��json����ΪUTF-8�����json�ĵ��������д���һ��QJsonDocument��
    // ��������ɹ�������QJsonDocument���󣬷��򷵻�null
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    // �ж��Ƿ����ʧ��
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json��ʽ����" << jsonError.error;
        return;
    }
    QJsonObject rootObj = doc.object();
    if (rootObj.value("Validation").toString() == "SUCCESS") {
        socket->disconnectFromHost();
        socket->close();
        QMessageBox::information(this, "Login", "SUCCESS");
        //this->close();
    }
    if (rootObj.value("Validation").toString() == "PASERROR") {
        socket->disconnectFromHost();
        socket->close();
        QMessageBox::information(this, "Login", "PASERROR");
    }
    if (rootObj.value("Validation").toString() == "NULLUSER") {
        socket->disconnectFromHost();
        socket->close();
        QMessageBox::information(this, "Login", "NULLUSER");
    }
}
